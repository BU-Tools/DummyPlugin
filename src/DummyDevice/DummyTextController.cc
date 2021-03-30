#include <DummyDevice/DummyTextController.hh>

DummyTextController::DummyTextController(std::ostream *os) {
    streams.push_back(os);
}

void DummyTextController::Print(const char *fmt, ...) {
    // wrapper around printerHelper to allow variable argument forwarding
    va_list argp;
    va_start(argp, fmt);
    printer Printer = printerHelper(fmt, argp);
    va_end(argp);

    std::vector<std::ostream*>::iterator it;
    for (it = streams.begin(); it != streams.end(); it++) {
        *(*it) << Printer;
    }
}

void DummyTextController::Print(printer a) {
    std::vector<std::ostream*>::iterator it;
    for (it = streams.begin(); it != streams.end(); it++) {
        *(*it) << a;
    }
}

void DummyTextController::AddOutputStream(std::ostream *os) {
    streams.push_back(os);
}

void DummyTextController::ResetStreams() {
    std::vector<std::ostream*>::iterator it;
    /*
    for (it = streams.begin(); it != streams.end(); it++) {
        delete (*it);
    }
    */
    streams.clear();
}