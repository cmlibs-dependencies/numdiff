cmake_minimum_required(VERSION 3.4)

project(numdiff VERSION 5.9.0)

set(SRC
    analyze.c
    arith.c
    bitvector.c
    cmpbuf.c
    cmpfns.c
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
    xmalloc.c
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

# Set config header with system environment. 
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/numdiff_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/numdiff_config.h)

# other files:
# errors.c error.c getopt.c new.c setmode.c number.c

add_executable(numdiff ${SRC} ${HDRS})

target_include_directories(numdiff PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

