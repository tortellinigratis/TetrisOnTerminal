#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#if defined(_WIN32) || defined(_WIN64)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#endif // PLATFORM_HPP

