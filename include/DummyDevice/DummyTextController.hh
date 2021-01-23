#ifndef __DUMMY_TEXT_CONTROLLER_HH__
#define __DUMMY_TEXT_CONTROLLER_HH__

//#include <Print/Print.hh>
#include "Print.hh"
#include <vector>
#include <memory>
#include <iostream>

class DummyTextController {
public:
    //void Print(std::vector<std::unique_ptr<std::ostream>>::iterator it, const char *fmt, ...);
    void Print(std::vector<std::unique_ptr<std::ostream>> v, const char *fmt, ...);
    void PrintDebug(const char *fmt, ...);
    void PrintError(const char *fmt, ...);
};

#endif