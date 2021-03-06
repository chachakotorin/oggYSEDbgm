/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building for ARM */
/* #undef CPU_ARM */

/* Define if building for MIPS */
/* #undef CPU_MIPS */

/* Define if building for X86 */
#define CPU_X86 /**/

/* Define to enable assembly optimizations */
#undef ENABLE_ASM

/* Define to enable FRW optimization */
/* #undef ENABLE_FRW */

/* Define to use SSE2 instructions */
#define ENABLE_SSE2 /**/

/* Define to use SSE4 instructions */
/* #undef ENABLE_SSE4 */

/* Define to 1 if you have the `aligned_alloc' function. */
//#define HAVE_ALIGNED_ALLOC 1

/* Define to 1 if you have the `lseek64' function. */
#define HAVE_LSEEK64 1

/* Define to 1 if you have the `malloc' function. */
#define HAVE_MALLOC 1

/* Define to 1 if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `read' function. */
#define HAVE_READ 1

/* Define to 1 if you have the `write' function. */
#define HAVE_WRITE 1

/* Name of package */
#define PACKAGE "libtta-cpp"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "info@true-audio.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "libtta-cpp"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libtta-cpp 2.3"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libtta-cpp"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.3"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "2.3"

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */
