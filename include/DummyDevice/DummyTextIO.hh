#ifndef __DUMMY_TEXT_IO_HH__
#define __DUMMY_TEXT_IO_HH__

#include <memory>   // std::unique_ptr
#include <vector>
#include <iostream>
//#include <DummyTextController/DummyTextController.hh>
#include "DummyTextController.hh"

class DummyTextIO {
public:
    // adds unique_ptr<ostream> to streams vector
    void AddOutputStream(std::unique_ptr<std::ostream>);
    // todo - clears streams vector? flushes their buffers? idk
    void ResetStreams();
protected:
    // vector containing unique_ptr to ostream objects
    std::vector<std::unique_ptr<std::ostream>> streams;
    // TextIOController -> should be able to access streams vector
   DummyTextController controller;
};

#endif 