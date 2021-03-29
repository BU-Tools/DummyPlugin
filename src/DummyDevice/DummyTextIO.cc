//#include <DummyTextIO/DummyTextIO.hh>
#include <DummyDevice/DummyTextIO.hh>

void DummyTextIO::AddOutputStream(std::ostream *stream,
                                  std::vector<std::ostream*> &streams) {
    streams.push_back(stream);
}

void DummyTextIO::AddOutputStream(std::ostringstream *stream,
                                  std::vector<std::ostringstream*> &streams) {
    streams.push_back(stream);
}

void DummyTextIO::AddOutputStream(std::ofstream *stream,
                                  std::vector<std::ofstream*> &streams) {
    streams.push_back(stream);
}


void DummyTextIO::ResetStreams(std::vector<std::ostream*> &streams) {
    // ptrs owned by DummyTextIO, must delete them before clearing vector
    // since not using smart pointers (yet)
    for (auto &ptr : streams) {
        delete &ptr;
    }
    streams.clear();
}

void DummyTextIO::PrintError(const char *fmt, ...) {
    // wrapper around printerHelper to allow variable argument forwarding
    va_list argp;
    va_start(argp, fmt);
    printer Printer = printerHelper(fmt, argp);
    va_end(argp);

    for (auto &stream : errorStreams) {
        //*stream << Printer(fmt);
        *stream << Printer;
    }
}

void DummyTextIO::PrintDebug(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    printer Printer = printerHelper(fmt, argp);
    va_end(argp);

    for (auto &stream : debugStreams) {
        *stream << Printer;
    }
}

void DummyTextIO::PrintString(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    printer Printer = printerHelper(fmt, argp);
    va_end(argp);

    for (auto &stream : stringStreams) {
        *stream << Printer;
    }
}

void DummyTextIO::PrintFile(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    printer Printer = printerHelper(fmt, argp);
    va_end(argp);

    for (auto &stream : fileStreams) {
        // presumably the file will have been initalized w/ a name
        *stream << Printer;
        stream->close();
    }
}