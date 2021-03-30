#ifndef __DUMMY_TEXT_CONTROLLER_HH__
#define __DUMMY_TEXT_CONTROLLER_HH__

#include "Print.hh"
#include "PrintLevel.hh"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

class DummyTextController {
private:
    std::vector<std::ostream*> streams;
public:
    DummyTextController(std::ostream *os);
    void Print(const char *fmt, ...);
    void Print(printer a);
    void AddOutputStream(std::ostream *os);
    void ResetStreams();
};

#endif