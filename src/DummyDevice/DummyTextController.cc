
//#include <DummyDevice/DummyTextController.hh>

/* 
   Pass the unique_ptrs by const l-value reference
   This ensures that the Print() function only uses 
   the unique_ptr for the duration of the fn's execution
 */

/*
void DummyTextController::Print(std::vector<std::unique_ptr<std::ostream>> const &v, const char *fmt, ...) {
   //debug - if streams vector empty, "Print() called" will be written to console twice
   std::cout << "Print() called" << std::endl;
   // iterate through vector, use << overload to enter formatted text to the ostreams
   for (auto &stream : v) {
       *stream.get() << Printer(fmt);
   }
   for (auto &stream : streams) {
       
   }
}



// other Print_() functionality to be added later
void DummyTextController::PrintDebug(const char *fmt, ...) {
    std::cout << Printer(fmt);
}

void DummyTextController::PrintError(const char *fmt, ...) {
    std::cout << Printer(fmt);
}
*/