%define name ustl
%define version 0.2
%define release 1

Summary:	uSTL - Codespace frugal STL implementation.
Name:		%{name}
Version:	%{version}
Release:	%{release}
Source0:	%{name}-%{version}.tar.gz
URL:		http://sourceforge.net/projects/ustl
License:	LGPL
Group:		Development/Libraries
Prefix:		%{_prefix}
BuildRoot:	%{buildroot}

%description
uSTL library reimplements the STL specification with the goal of
reducing code duplication that STL templates normally produce. uSTL
attempts to do this by factoring out memory-management code into a
non-template base class.

%prep
%setup -q

%build
./configure --prefix=%{buildroot}%{_prefix}
make

%install
make install

%files
%defattr(-,root,root)
%{_prefix}/lib/libustl.a
%{_prefix}/include/ustl.h
%{_prefix}/include/ustl/
%{_prefix}/include/ustl/cmemlink.h
%{_prefix}/include/ustl/fdostream.h
%{_prefix}/include/ustl/memblock.h
%{_prefix}/include/ustl/memlink.h
%{_prefix}/include/ustl/mistream.h
%{_prefix}/include/ustl/mostream.h
%{_prefix}/include/ustl/sistream.h
%{_prefix}/include/ustl/sostream.h
%{_prefix}/include/ustl/strmsize.h
%{_prefix}/include/ustl/ualgo.h
%{_prefix}/include/ustl/uctralgo.h
%{_prefix}/include/ustl/uexception.h
%{_prefix}/include/ustl/ufunction.h
%{_prefix}/include/ustl/uios.h
%{_prefix}/include/ustl/uiosfunc.h
%{_prefix}/include/ustl/uiterator.h
%{_prefix}/include/ustl/ulimits.h
%{_prefix}/include/ustl/umap.h
%{_prefix}/include/ustl/umultimap.h
%{_prefix}/include/ustl/umultiset.h
%{_prefix}/include/ustl/unew.h
%{_prefix}/include/ustl/upair.h
%{_prefix}/include/ustl/uset.h
%{_prefix}/include/ustl/uspecial.h
%{_prefix}/include/ustl/ustack.h
%{_prefix}/include/ustl/ustring.h
%{_prefix}/include/ustl/utypes.h
%{_prefix}/include/ustl/uutility.h
%{_prefix}/include/ustl/uvector.h
%{_prefix}/include/ustl/utf8.h
%doc COPYING README docs/html bvt