cmake_minimum_required(VERSION 3.4)

project(numdiff VERSION 5.9.0)

set(SRC
    analyze.c
    arith.c
    bitvector.c
    cmpbuf.c
    cmpfns.c
    error.c
    exitfail.c
    flags.c
    inout.c
    io.c
    linesplit.c
    main.c
    numutil.c
    options.c
    side.c
    thrlist.c
    util.c
    xalloc-die.c
    xmalloc.cxx
)

set(HDRS
    bitvector.h
    cmpbuf.h
    config.h
    error.h
    exitfail.h
    getopt.h
    getopt_int.h
    gettext.h
    linesplit.h
    ndselect.h
    number.h
    numdiff.h
    setmode.h
    system.h
    unlocked-io.h
    xalloc.h
)

# Run configuration tests.
include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckLibraryExists)
include(CheckFunctionExists)
include(CheckStructHasMember)
include(CheckCSourceCompiles)
include(CheckCXXSourceCompiles)

check_type_size("long long" HAVE_LONG_LONG)

check_include_file(string.h HAVE_STRING_H)
check_include_file(float.h HAVE_FLOAT_H)
check_include_file(stdarg.h HAVE_STDARG_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(fcntl.h HAVE_FCNTL_H)
check_include_file(stdbool.h HAVE_STDBOOL_H)
check_include_file(time.h HAVE_TIME_H)
check_include_file(sys/file.h HAVE_SYS_FILE_H)
check_include_file(sys/wait.h HAVE_SYS_WAIT_H)
check_include_file(dirent.h HAVE_DIRENT_H)
check_include_file(sys/ndir.h HAVE_SYS_NDIR_H)
check_include_file(sys/dir.h HAVE_SYS_DIR_H)
check_include_file(ndir.h HAVE_NDIR_H)
check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(locale.h HAVE_LOCALE_H)
if (HAVE_STRING_H AND HAVE_FLOAT_H AND HAVE_STDARG_H AND HAVE_STDLIB_H)
    set(STDC_HEADERS 1)
endif ()

check_symbol_exists(localeconv "locale.h" HAVE_LOCALECONV)
check_symbol_exists(clearerr_unlocked "stdio.h" HAVE_DECL_CLEARERR_UNLOCKED)
check_symbol_exists(feof_unlocked "stdio.h" HAVE_DECL_FEOF_UNLOCKED)
check_symbol_exists(ferror_unlocked "stdio.h" HAVE_DECL_FERROR_UNLOCKED)
check_symbol_exists(fflush_unlocked "stdio.h" HAVE_DECL_FFLUSH_UNLOCKED)
check_symbol_exists(fgets_unlocked "stdio.h" HAVE_DECL_FGETS_UNLOCKED)
check_symbol_exists(fputc_unlocked "stdio.h" HAVE_DECL_FPUTC_UNLOCKED)
check_symbol_exists(fputs_unlocked "stdio.h" HAVE_DECL_FPUTS_UNLOCKED)
check_symbol_exists(fread_unlocked "stdio.h" HAVE_DECL_FREAD_UNLOCKED)
check_symbol_exists(fwrite_unlocked "stdio.h" HAVE_DECL_FWRITE_UNLOCKED)
check_symbol_exists(getchar_unlocked "stdio.h" HAVE_DECL_GETCHAR_UNLOCKED)
check_symbol_exists(getc_unlocked "stdio.h" HAVE_DECL_GETC_UNLOCKED)
check_symbol_exists(putchar_unlocked "stdio.h" HAVE_DECL_PUTCHAR_UNLOCKED)
check_symbol_exists(putc_unlocked "stdio.h" HAVE_DECL_PUTC_UNLOCKED)

check_struct_has_member("struct stat" st_rdev sys/stat.h HAVE_ST_RDEV)

check_function_exists(calloc HAVE_CALLOC)
check_function_exists(strchr HAVE_STRCHR)
check_function_exists(memchr HAVE_MEMCHR)
check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
if (NOT HAVE_CLOCK_GETTIME)
    check_library_exists(rt clock_gettime "time.h" HAVE_CLOCK_GETTIME)
    set(ADDITIONAL_LIBS rt)
endif ()
check_function_exists(strerror_r HAVE_STRERROR_R)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)

check_cxx_source_compiles(
  "static inline int test (void) {return 0;}\nint main (void) {return test();}"
  HAVE_INLINE)

check_c_source_compiles( "#include <string.h>
int main() {
char * c;
c = strerror_r(0,c,0);
return 0;
}" STRERROR_R_CHAR_P )

# function is declared with the above
if (STRERROR_R_CHAR_P)
    set(HAVE_DECL_STRERROR_R 1)
else ()
    set(HAVE_DECL_STRERROR_R 0)
endif ()

# Check for gmp
check_include_file(gmp.h HAVE_GMP_H)
if (HAVE_GMP_H)
    find_library(GMP_LIBRARY gmp)
    if (GMP_LIBRARY)
        set(HAVE_LIBGMP TRUE)
    endif ()
endif ()

if (WIN32)
    set(HAVE_SETMODE_DOS 1)
endif ()

# Set config header with system environment. 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/numdiff_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/numdiff_config.h)

# other files:
# errors.c error.c getopt.c new.c setmode.c number.c

add_executable(numdiff ${SRC} ${HDRS})
set_target_properties(numdiff PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(numdiff PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
if (HAVE_LIBGMP)
    target_link_libraries(numdiff PUBLIC ${GMP_LIBRARY})
endif ()
if (ADDITIONAL_LIBS)
    target_link_libraries(numdiff PUBLIC ${ADDITIONAL_LIBS})
endif ()

install(TARGETS numdiff DESTINATION bin)
