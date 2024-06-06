#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#if defined(_WIN32) || defined(_WIN64)
    #include <ncurses/ncurses.h>
#elif defined(__linux__)
    #include <ncurses.h>
#elif defined(__APPLE__)
    #include <ncurses.h>
    #if TARGET_OS_MAC
        #include <ncurses.h>
    #endif
#else
    #error "Unknown platform"
#endif

#endif // PLATFORM_HPP
