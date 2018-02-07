cmake_minimum_required(VERSION 2.8)

project(numdiff)

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

# other files:
# errors.c error.c getopt.c new.c setmode.c number.c

add_executable(numdiff ${SRC} ${HDRS})
