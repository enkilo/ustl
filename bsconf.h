#define PACKAGE_NAME		"ustl"
#define LIB_MAJOR		"0"
#define LIB_MINOR		"4"
#define LIB_BUILD		"2"

#define PACKAGE_VERSION		LIB_MAJOR "." LIB_MINOR
#define PACKAGE_TARNAME		PACKAGE_NAME
#define PACKAGE_STRING		PACKAGE_NAME " " PACKAGE_VERSION
#define PACKAGE_BUGREPORT	"Mike Sharov <msharov@talentg.com>"

static string_t g_Files [] = {
    "Common.mk",
    "config.h",
    "ustl.spec"
};

static string_t g_EnvVars [] = {
    "CC",
    "LD",
    "CXX",
    "CPP",
    "HOME",
    "CXXFLAGS",
    "LDFLAGS",
    "CPPFLAGS",
    "CFLAGS"
};

/*  VARIABLE	PROGRAM		HOW TO CALL	IF NOT FOUND */
static string_t g_ProgVars [] = {
    "CC",	"cc",		"cc",		"gcc",
    "CXX",	"c++",		"c++",		"g++",
    "LD",	"ld",		"ld",		"ld",
    "AR",	"ar",		"ar",		"echo",
    "RANLIB",	"ranlib",	"ranlib",	"touch",
    "DOXYGEN",	"doxygen",	"doxygen",	"echo",
    "INSTALL",	"install",	"install -c",	"cp",
    "RM",	"rm",		"rm -f",	"rm",
    "LN",	"ln",		"ln -sf",	"cp"
};

static string_t	g_Headers [] = {
    "fcntl.h",		"#undef HAVE_FCNTL_H",		"#define HAVE_FCNTL_H 1",
    "float.h",		"#undef HAVE_FLOAT_H",		"#define HAVE_FLOAT_H 1",
    "inttypes.h",	"#undef HAVE_INTTYPES_H",	"#define HAVE_INTTYPES_H 1",
    "limits.h",		"#undef HAVE_LIMITS_H",		"#define HAVE_LIMITS_H 1",
    "malloc.h",		"#undef HAVE_MALLOC_H",		"#define HAVE_MALLOC_H 1",
    "alloca.h",		"#undef HAVE_ALLOCA_H",		"#define HAVE_ALLOCA_H 1",
    "memory.h",		"#undef HAVE_MEMORY_H",		"#define HAVE_MEMORY_H 1",
    "stddef.h",		"#undef HAVE_STDDEF_H",		"#define HAVE_STDDEF_H 1",
    "stdint.h",		"#undef HAVE_STDINT_H",		"#define HAVE_STDINT_H 1",
    "stdlib.h",		"#undef HAVE_STDLIB_H",		"#define HAVE_STDLIB_H 1",
    "string.h",		"#undef HAVE_STRING_H",		"#define HAVE_STRING_H 1",
    "strings.h",	"#undef HAVE_STRINGS_H",	"#define HAVE_STRINGS_H 1",
    "sys/stat.h",	"#undef HAVE_SYS_STAT_H",	"#define HAVE_SYS_STAT_H 1",
    "sys/types.h",	"#undef HAVE_SYS_TYPES_H",	"#define HAVE_SYS_TYPES_H 1",
    "sys/wait.h",	"#undef HAVE_SYS_WAIT_H",	"#define HAVE_SYS_WAIT_H 1",
    "unistd.h",		"#undef HAVE_UNISTD_H",		"#define HAVE_UNISTD_H 1",
    "byteswap.h",	"#undef HAVE_BYTESWAP_H",	"#define HAVE_BYTESWAP_H 1",
    "stdlib.h",		"#undef STDC_HEADERS",		"#define STDC_HEADERS 1"
};

static string_t g_Functions [] = {
    "atexit",		"#undef HAVE_ATEXIT",		"#define HAVE_ATEXIT 1",
    "malloc",		"#undef HAVE_MALLOC\n",		"#define HAVE_MALLOC 1\n",
    "memchr",		"#undef HAVE_MEMCHR",		"#define HAVE_MEMCHR 1",
    "memmove",		"#undef HAVE_MEMMOVE",		"#define HAVE_MEMMOVE 1",
    "memset",		"#undef HAVE_MEMSET",		"#define HAVE_MEMSET 1",
    "ptrdiff_t",	"#undef HAVE_PTRDIFF_T",	"#define HAVE_PTRDIFF_T 1",
    "strerror",		"#undef HAVE_STRERROR",		"#define HAVE_STRERROR 1",
    "strsignal",	"#undef HAVE_STRSIGNAL",	"#define HAVE_STRSIGNAL 1",
    "strtol",		"#undef HAVE_STRTOL",		"#define HAVE_STRTOL 1",
    "strrchr",		"#undef HAVE_STRRCHR",		"#define HAVE_STRRCHR 1"
};

static string_t g_Components [] = {
    "debug",		"#DEBUG\t\t= 1 ",			"DEBUG\t\t= 1",
    "bounds",		"#undef WANT_STREAM_BOUNDS_CHECKING",	"#define WANT_STREAM_BOUNDS_CHECKING 1 ",
    "cout",		"#define WITHOUT_CIN_COUT_CERR 1",	"#undef WITHOUT_CIN_COUT_CERR",
    "libstdc++",	"#define WITHOUT_LIBSTDCPP 1",		"#undef WITHOUT_LIBSTDCPP",
    "libstdc++",	"STANDALONE\t= -nodefaultlibs ",	"#STANDALONE\t= -nodefaultlibs"
};

static SComponentInfo g_ComponentInfos [VectorSize(g_Components) / 3] = {
    { 0, "Compiles the library with debugging information" },
    { 0, "Enable runtime bounds checking on stream reads/writes" },
    { 1, "Removes support for standard cout/cin/cerr streams" },
#if (__GNUC__ >= 3)
    { 1, "Allows user programs to not link with libstdc++" },
#else
    { 1, "" },
#endif
    { 1, "" }
};

static string_t g_CustomVars [] = {
    "PACKAGE_NAME",		PACKAGE_NAME,
    "PACKAGE_VERSION",		PACKAGE_VERSION,
    "PACKAGE_TARNAME",		PACKAGE_TARNAME,
    "PACKAGE_STRING",		PACKAGE_STRING,
    "PACKAGE_BUGREPORT",	PACKAGE_BUGREPORT,
    "LIBNAME",			PACKAGE_NAME,
    "LIB_MAJOR",		LIB_MAJOR,
    "LIB_MINOR",		LIB_MINOR,
    "LIB_BUILD",		LIB_BUILD
};

