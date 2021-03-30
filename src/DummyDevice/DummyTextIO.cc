#include <DummyDevice/DummyTextIO.hh>

DummyTextIO::DummyTextIO(void) {
    for (int i=0; i<3; i++) {
        // just to instantiate the Controllers with some stream - can change later
        controllers.push_back(DummyTextController(&std::cout));
    }
}

void DummyTextIO::AddOutputStream(Level::level level, std::ostream *os) {
    controllers[level].AddOutputStream(os);
}

void DummyTextIO::ResetStreams(Level::level level) {
    controllers[level].ResetStreams();
}

void DummyTextIO::Print(Level::level level, const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    printer Printer = printerHelper(fmt, argp);
    va_end(argp);

    controllers[level].Print(Printer);

    // after Print call, free storage allocated to the char buffer
    // vasprintf provides a ptr to malloc'd storage - must be free'd by caller
    free(Printer.s);
}
