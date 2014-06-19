// This file is part of the uSTL library, an STL implementation.
//
// Copyright (c) 2005 by Mike Sharov <msharov@users.sourceforge.net>
// This file is free software, distributed under the MIT License.

#include "fstream.h"
#include "uexception.h"
#include "uutility.h"

#ifdef MAPIP
#include <maapi.h>
#else
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#endif
#if HAVE_SYS_MMAN_H
    #include <sys/mman.h>
#endif

namespace ustl {

/// Default constructor.
fstream::fstream (void) noexcept
: ios_base (),
  m_fd (-1),
  m_Filename ()
{
    exceptions (goodbit);
}

/// Opens \p filename in \p mode.
fstream::fstream (const char* filename, openmode mode)
: ios_base (),
  m_fd (-1),
  m_Filename ()
{
    exceptions (goodbit);
    open (filename, mode);
}

/// Attaches to \p nfd of \p filename.
fstream::fstream (int nfd, const char* filename)
: ios_base (),
  m_fd (-1),
  m_Filename ()
{
    exceptions (goodbit);
    attach (nfd, filename);
}

/// Destructor. Closes if still open, but without throwing.
fstream::~fstream (void) noexcept
{
    clear (goodbit);
    exceptions (goodbit);
    close();
    assert (!(rdstate() & badbit) && "close failed in the destructor! This may lead to loss of user data. Please call close() manually and either enable exceptions or check the badbit.");
}

/// Sets state \p s and throws depending on the exception setting.
void fstream::set_and_throw (iostate s, const char* op)
{
    if (ios_base::set_and_throw (s))
#ifdef MAPIP
        maPanic(0,name());
#else
	throw file_exception (op, name());
#endif
}

/// Attaches to the given \p nfd.
void fstream::attach (int nfd, const char* filename)
{
    assert (filename && "Don't do that");
    m_Filename = filename;
    clear (goodbit);
    if (nfd < 0)
	set_and_throw (badbit, "open");
    close();
    m_fd = nfd;
}

/// Detaches from the current fd.
void fstream::detach (void) noexcept
{
    m_fd = -1;
    m_Filename.clear();
}

/// Converts openmode bits into libc open flags.
/*static*/ int fstream::om_to_flags (openmode m) noexcept
{
    int flags;
#ifdef MAPIP
    flags  = MA_ACCESS_READ;
    if((m & (out|app|trunc)))
        flags = MA_ACCESS_READ_WRITE;
#else
    static const int s_OMFlags [nombits] = {
	0,		// in
	O_CREAT,	// out
	O_APPEND,	// app
	O_APPEND,	// ate
	0,		// binary
	O_TRUNC,	// trunc
	O_NONBLOCK,	// nonblock
	0,		// nocreate
	O_NOCTTY	// noctty
    };
    if (O_RDONLY == in-1 && O_WRONLY == out-1 && O_RDWR == (in|out)-1)
	flags = (m - 1) & O_ACCMODE;
    else
	flags = ((m&(in|out))==(in|out)) ? O_RDWR : ((m&out) ? O_WRONLY : O_RDONLY);
    for (uoff_t i = 0; i < VectorSize(s_OMFlags); ++ i)
	flags |= s_OMFlags[i] & (!(m&(1<<i))-1);
    if (m & nocreate)
	flags &= ~O_CREAT;
#endif
    return (flags);
}

/// \brief Opens \p filename in the given mode.
/// \warning The string at \p filename must exist until the object is closed.
void fstream::open (const char* filename, openmode mode, mode_t perms)
{
    int nfd = 
#ifdef MAPIP
        maFileOpen(filename, om_to_flags(mode));
        if(nfd < 0) return;
        if(!(mode & (out|app|trunc))) {
            if(!maFileExists(nfd))
                return;
        } else {
            if(mode & app)
                maFileSeek(nfd,0,MA_SEEK_END);
            else if(mode & trunc)
                maFileTruncate(nfd,0);
            else
                maFileCreate(nfd);
        }
#else
        ::open (filename, om_to_flags(mode), perms);
#endif
    attach (nfd, filename);
}

/// Closes the file and throws on error.
void fstream::close (void)
{
    if (m_fd < 0)
	return;	// already closed
#ifdef MAPIP
    maFileClose(m_fd);
#else
    while (::close(m_fd)) {
	if (errno != EINTR) {
	    set_and_throw (badbit | failbit, "close");
	    break;
	}
    }
#endif
    detach();
}

/// Moves the current file position to \p n.
off_t fstream::seek (off_t n, seekdir whence)
{
    off_t p = 
#ifdef MAPIP
        maFileSeek(m_fd, n, whence);
#else
        lseek (m_fd, n, whence);
#endif
    if (p < 0)
	set_and_throw (failbit, "seek");
    return (p);
}

/// Returns the current file position.
off_t fstream::pos (void) const noexcept
{
    return
#ifdef MAPIP
      maFileTell(m_fd);
#else
      lseek (m_fd, 0, SEEK_CUR);
 #endif
}

/// Reads \p n bytes into \p p.
off_t fstream::read (void* p, off_t n)
{
    off_t br (0);
    while ((br < n) & good())
	br += readsome (advance (p, br), n - br);
    return (br);
}

/// Reads at most \p n bytes into \p p, stopping when it feels like it.
off_t fstream::readsome (void* p, off_t n)
{
    ssize_t brn;
    do { brn = 
#ifdef MAPIP
        maFileRead(m_fd, p, n);
    } while(0);
    if (brn >= 0) return n;
    else if(brn < 0) {
#else
        ::read (m_fd, p, n); 
    } while ((brn < 0) & (errno == EINTR));
    if (brn > 0) return (brn);
    else if ((brn < 0) & (errno != EAGAIN)) {
#endif
 	set_and_throw (failbit, "read");
    }
    else if (!brn && ios_base::set_and_throw (eofbit | failbit))
#ifdef MAPIP
maPanic(0,"failed fstream::readsome");
#else
	throw stream_bounds_exception ("read", name(), pos(), n, 0);
#endif
    return (0);
}

/// Writes \p n bytes from \p p.
off_t fstream::write (const void* p, off_t n)
{
    off_t btw (n);
    while (btw) {
	const off_t bw (n - btw);
	ssize_t bwn; 
#ifdef MAPIP
	if(m_fd == (int)&maWriteLog) {
		if((bwn = maWriteLog(advance(p,bw),btw)) >= 0)
			bwn = btw;
	} else {
		if((bwn = maFileWrite(m_fd, advance(p,bw), btw)) >= 0)
			bwn = btw;
	}
#else
      bwn = ::write (m_fd, advance(p,bw), btw);
#endif
	if (bwn > 0)
	    btw -= bwn;
#ifndef MAPIP
	else if (!bwn) {
	    if (ios_base::set_and_throw (eofbit | failbit))
#ifdef MAPIP
    maPanic(0,"failed fstream::write");
#else
		throw stream_bounds_exception ("write", name(), pos() - bw, n, bw);
#endif
	    break;
	} 
  else if (errno != EINTR) {
	    if (errno != EAGAIN)
#else
  else {
#endif
      if(bwn < 0)
		set_and_throw (failbit, "write");
	    break;
	}
    }
    return (n - btw);
}

/// Returns the file size.
off_t fstream::size (void) const
{
#ifdef MAPIP
    return maFileSize(m_fd);
#else
    struct stat st;
    st.st_size = 0;
    stat (st);
    return (st.st_size);
#endif
}

/// Synchronizes the file's data and status with the disk.
void fstream::sync (void)
{
#ifndef MAPIP
    if (fsync (m_fd))
	set_and_throw (badbit | failbit, "sync");
#endif
}

/// Get the stat structure.
void fstream::stat (struct stat& rs) const
{
#ifndef MAPIP
    if (fstat (m_fd, &rs))
	throw file_exception ("stat", name());
#else
    maPanic(0,"fstream::stat not implemented");
#endif
}

/// Calls the given ioctl. Use IOCTLID macro to pass in both \p name and \p request.
int fstream::ioctl (const char* rname, int request, long argument)
{
#ifndef MAPIP
    int rv = ::ioctl (m_fd, request, argument);
    if (rv < 0)
	set_and_throw (failbit, rname);
    return (rv);
#else
    maPanic(0,"fstream::ioctl not implemented");
#endif
}

/// Calls the given fcntl. Use FCNTLID macro to pass in both \p name and \p request.
int fstream::fcntl (const char* rname, int request, long argument)
{
#ifndef MAPIP
    int rv = ::fcntl (m_fd, request, argument);
    if (rv < 0)
	set_and_throw (failbit, rname);
    return (rv);
#else
    maPanic(0,"fstream::fnctl not implemented");
    return -1;
#endif
}

void fstream::set_nonblock (bool v) noexcept
{
#ifndef MAPIP
    int curf = max (0, fcntl (FCNTLID (F_GETFL)));
    if (v) curf |=  O_NONBLOCK;
    else   curf &= ~O_NONBLOCK;
    fcntl (FCNTLID (F_SETFL), curf);
#endif
}

#if HAVE_SYS_MMAN_H

/// Memory-maps the file and returns a link to it.
memlink fstream::mmap (off_t n, off_t offset)
{
    void* result = ::mmap (NULL, n, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, offset);
    if (result == MAP_FAILED)
	set_and_throw (failbit, "mmap");
    return (memlink (result, n));
}

/// Unmaps a memory-mapped area.
void fstream::munmap (memlink& l)
{
    if (::munmap (l.data(), l.size()))
	set_and_throw (failbit, "munmap");
    l.unlink();
}

/// Synchronizes a memory-mapped area.
void fstream::msync (memlink& l)
{
    if (::msync (l.data(), l.size(), MS_ASYNC | MS_INVALIDATE))
	set_and_throw (failbit, "msync");
}

#endif

} // namespace ustl
