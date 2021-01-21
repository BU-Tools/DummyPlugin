//#include <DummyTextController/DummyTextController.hh>
#include <DummyDevice/DummyTextController.hh>

void DummyTextController::Print(const char *fmt, ...) {
    std::cout << Printer(fmt);
    // ^ we want to replace std::cout with a ref. to the unique_ptr<ostream>
    // or multiple such unique_ptrs so that we can write to it
}

void DummyTextController::PrintDebug(const char *fmt, ...) {
    std::cout << Printer(fmt);
    /*
    for (auto &stream : streams) {
        *stream << Printer(fmt);
    }
    */
}

void DummyTextController::PrintError(const char *fmt, ...) {
    std::cout << Printer(fmt);
}