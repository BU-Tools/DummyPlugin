#include <DummyDevice/Print.hh>

printer printerHelper(const char *fmt, va_list argp) {
    printer a;
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wformat-nonliteral"
    vasprintf(&a.s, fmt, argp);
    #pragma GCC diagnostic pop
    return a;
}

std::ostream& operator<<(std::ostream& os, printer b) {
    os<<b.s;
    //free(b.s);
    return os;
}