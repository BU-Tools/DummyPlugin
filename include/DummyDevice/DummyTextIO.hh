#ifndef __DUMMY_TEXT_IO_HH__
#define __DUMMY_TEXT_IO_HH__

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
//#include <streambuf>
#include "Print.hh"

class DummyTextIO {
public:
    // adds ptr to ostream to streams vector
    void AddOutputStream(std::ostream *stream, 
                         std::vector<std::ostream*> &streams);
    void AddOutputStream(std::ostringstream *stream, 
                         std::vector<std::ostringstream*> &streams);
    void AddOutputStream(std::ofstream *stream, 
                         std::vector<std::ofstream*> &streams);                

    // deletes pointers, clears the vector
    void ResetStreams(std::vector<std::ostream*> &streams);

    // allow Printer to operate on protected stream vectors
    //friend std::ostream& operator<<(std::ostream& os, printer a);

    /* print functions */
    void PrintError(const char *fmt, ...);
    void PrintDebug(const char *fmt, ...);
    void PrintString(const char *fmt, ...);
    void PrintFile(const char *fmt, ...);

protected:  
    std::vector<std::ostream*> errorStreams;         // stderr
    std::vector<std::ostream*> debugStreams;         // stdout
    std::vector<std::ostringstream*> stringStreams;   // sstreams
    std::vector<std::ofstream*> fileStreams;         // fstreams
};

#endif 