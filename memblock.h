// This file is part of the ustl library, an STL implementation.
// Copyright (C) 2003 by Mike Sharov <msharov@talentg.com>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the 
// Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
// Boston, MA  02111-1307  USA.
//
// memblock.h
//
/** \class ustl::memblock
 *
 * \brief Allocated memory block.
 * Adds memory management capabilities to memlink. Uses malloc and realloc to
 * maintain the internal pointer, but only if allocated using members of this class,
 * or if linked to using the Manage() member function. Managed memory is automatically
 * freed in the destructor.
 *
 * @see memlink
*/

#ifndef MEMBLOCK_H
#define MEMBLOCK_H

#include "memlink.h"

namespace ustl {

class memblock : public memlink {
public:
    static const size_t c_DefaultPageSize = 16;			///< The default minimum allocation unit.
    static const size_t	c_MinimumShrinkSize = ((1 << 16) - 1);	///< reserve will shrink reallocated block if this much unused space results.
public:
			memblock (void);
    explicit		memblock (size_t n);
			memblock (void* p, size_t n);
			memblock (const void* p, size_t n);
    explicit		memblock (const cmemlink& b);
    explicit		memblock (const memblock& b);
    virtual	       ~memblock (void);
    const memblock&	operator= (const cmemlink& b);
    const memblock&	operator= (const memlink& b);
    const memblock&	operator= (const memblock& b);
    void		assign (const cmemlink& l);
    void		swap (memblock& l);
    void		reserve (size_t newSize);
    void		resize (size_t newSize);
    iterator		insert (iterator start, size_t size);
    iterator		erase (iterator start, size_t size);
    inline void		clear (void);
    void		deallocate (void);
    void		manage (void* p, size_t n);
    inline void		manage (memlink& l);
    inline void		setPageSize (size_t n);
    inline size_t	pageSize (void) const;
    inline size_t	capacity (void) const;
    virtual void	unlink (void);
    inline size_t	max_size (void) const;
    virtual void	read (istream& is);
    void		read_file (const char* filename);
    inline bool		is_linked (void) const;
private:
    size_t		m_AllocatedSize;	///< Number of bytes allocated by Resize.
    size_t		m_PageSize;		///< The minimum allocation unit.
};

/// Sets the minimum allocation unit.
inline void memblock::setPageSize (size_t n)
{
    m_PageSize = n;
}

/// Returns the number of bytes allocated.
inline size_t memblock::capacity (void) const
{
    return (m_AllocatedSize);
}

/// Returns the current page size.
inline size_t memblock::pageSize (void) const
{
    return (m_PageSize);
}

/// Assumes control over block pointed to by \p l
inline void memblock::manage (memlink& l)
{
    manage (l.begin(), l.size());
}

/// Returns the maximum possible size of the block
inline size_t memblock::max_size (void) const
{
    return (numeric_limits<size_t>::max());
}

/// Resizes the block to 0
inline void memblock::clear (void)
{
    resize (0);
}

inline bool memblock::is_linked (void) const
{
    return (!m_AllocatedSize && cdata());
}

} // namespace ustl

#endif
