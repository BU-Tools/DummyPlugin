#ifndef __DUMMY_TEXT_CONTROLLER_HH__
#define __DUMMY_TEXT_CONTROLLER_HH__

/*
//#include <Print/Print.hh>
#include "Print.hh"
#include <vector>
#include <memory>
#include <iostream>

class DummyTextController {
public:
    //void Print(std::vector<std::unique_ptr<std::ostream>>::iterator it, const char *fmt, ...);    // get unique_ptr element of vector, addressed by iterator argument
    //void Print(std::vector<std::unique_ptr<std::ostream>> v, const char *fmt, ...);               // pass vector directly -> std::move cleared unique_ptr<ostream> from vector after function execution
    void Print(std::vector<std::unique_ptr<std::ostream>> const &v, const char *fmt, ...);          // pass vector by const l-value reference
    void PrintDebug(const char *fmt, ...);
    void PrintError(const char *fmt, ...);
};
*/

#endif