//#define _GNU_SOURCE
#include <cstdarg>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <DummyDevice/Print.hh>

printer Printer(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    printer a;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
	vasprintf(&a.s, fmt, ap);
#pragma GCC diagnostic pop
	va_end(ap);
	return a;
}

std::ostream& operator<<(std::ostream& os, printer a) {
    os<<a.s;
    free(a.s);
    return os;
}