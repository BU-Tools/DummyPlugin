//#include <DummyTextController/DummyTextController.hh>
#include <DummyDevice/DummyTextController.hh>

/*
void DummyTextController::Print(std::vector<std::unique_ptr<std::ostream>>::iterator it, const char *fmt, ...) {
    std::cout << Printer(fmt);
    // ^ we want to replace std::cout with a ref. to the unique_ptr<ostream>
    // or multiple such unique_ptrs so that we can write to it
    
    for (auto &stream : streams) {
        *stream.get() << Printer(fmt);
    }
    
   for (auto const& i: it) {
       (*it)->i.get() << Printer(fmt);
   }
    //(*it)->std::ostream.rdbuf() << Printer(fmt);
}
*/

void DummyTextController::Print(std::vector<std::unique_ptr<std::ostream>> v, const char *fmt, ...) {
    /*
    for (auto it = v.begin(); it != v.end();) {
        //(*it)->get() << Printer(fmt);     // error: ‘class std::basic_ostream<char>’ has no member named ‘get’
        //(*it) << Printer(fmt);            // error: no match for ‘operator<<’ (operand types are ‘std::unique_ptr<std::basic_ostream<char> >’ and printer’)
        //it << Printer(fmt);               // no match for operator <<
        //(*it).get() << Printer(fmt);      // no match for operator <<
        *it << Printer(fmt);
    }
    */
   //debug 
   std::cout << "Print() called" << std::endl;
   for (auto &stream : v) {
       *stream.get() << Printer(fmt);
   }
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