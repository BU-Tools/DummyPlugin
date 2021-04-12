#ifndef _DUMMY_DEVICE_HH__
#define _DUMMY_DEVICE_HH__

// for tool device base class
#include <BUTool/CommandList.hh>
#include <BUTool/DeviceFactory.hh>

#include <string>
#include <iostream>
#include <memory>
#include <sstream>

#include <map>  // mapping commands and their aliases

#include <Dummy/Dummy.hh>
#include "DummyTextIO.hh"

namespace BUTool {

  class DummyDevice : public DummyTextIO, public CommandList<DummyDevice> {
  public:
    // vector of strings -> ofstream
    DummyDevice(std::vector<std::string> arg);
    ~DummyDevice();
  private:
    DummyDevice();
    Dummy * myDummy = NULL;
    
    // update map beteen string and function
    void LoadCommandList();

    // add new commands here
    // instantiates the Dummy obj
    CommandReturn::status Start(std::vector<std::string>, std::vector<uint64_t>);
    // performs a given operation
    CommandReturn::status Operations(std::vector<std::string>, std::vector<uint64_t>);

    // perform the operations individually
    CommandReturn::status Add(std::vector<std::string>, std::vector<uint64_t>);
    CommandReturn::status Subtract(std::vector<std::string>, std::vector<uint64_t>);
    CommandReturn::status Multiply(std::vector<std::string>, std::vector<uint64_t>);

    // call to AddOutputStream() and ResetStreams() in TextIO class
    /* these should not be user-facing functions */
    //CommandReturn::status AddStream(std::vector<std::string>, std::vector<uint64_t>);
    //CommandReturn::status ResetStream(std::vector<std::string>, std::vector<uint64_t>);

    // test Print() method
    CommandReturn::status PrintTest(std::vector<std::string>, std::vector<uint64_t>);

    // testing out writing to and reading from a stringstream
    CommandReturn::status StringTest(std::vector<std::string>, std::vector<uint64_t>);

    // testing out writing to multiple streams at once
    CommandReturn::status FileTest(std::vector<std::string>, std::vector<uint64_t>);

    // testing a method for getting all registered commands & aliases
    // the idea is to have some means of automatically wrapping existing commands for the apollo-herd plugin
    CommandReturn::status GetCommands(std::vector<std::string>, std::vector<uint64_t>);
    std::map<std::string, std::vector<std::string> > commandList;
  };

    // register Dummydevice with factory
  RegisterDevice(DummyDevice,    // class Name
		 "Dummy",        // class nickname 
		 "",             // class help
		 "d",            // CLI flag 
		 "dummy",        // CLI full flag 
		 ""              // CLI description
		 );
  
}   // namespace BUTool

#endif
