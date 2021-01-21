// adapted from https://github.com/WingTillDie/CxxPrintf

#ifndef __PRINT_HH__
#define __PRINT_HH__
//#pragma once

#include <iostream>

struct printer {
    char *s;
};

printer Printer(const char *fmt, ...);
std::ostream& operator<<(std::ostream& os, printer a);

#endif