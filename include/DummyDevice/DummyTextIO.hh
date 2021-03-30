#ifndef __DUMMY_TEXT_IO_HH__
#define __DUMMY_TEXT_IO_HH__

#include "DummyTextController.hh"

class DummyTextIO {
public:
    DummyTextIO();
    void AddOutputStream(Level::level level, std::ostream *os);
    void ResetStreams(Level::level level);
    void Print(Level::level level, const char *fmt, ...);
private:
    //DummyTextController Controller;
    std::vector<DummyTextController> controllers;
};

#endif 