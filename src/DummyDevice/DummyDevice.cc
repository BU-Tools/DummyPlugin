#include <DummyDevice/DummyDevice.hh>

#include<string>
#include <iostream>

using namespace BUTool;

DummyDevice::DummyDevice(std::vector<std::string> /*arg*/)
  : CommandList<DummyDevice>("Dummy"),
    myDummy(NULL) {
  myDummy = new Dummy();
  //setup commands
  LoadCommandList();  
}

DummyDevice::~DummyDevice() {
  if (myDummy) {
    delete myDummy;
  }
}

void DummyDevice::LoadCommandList() {
    // general commands (launcher commands)
    AddCommand("start",&DummyDevice::Start,
                "instantiates the dummy\n" \
                " Usage:\n"                \
                " start\n");

    AddCommand("operations",&DummyDevice::Operations,
                "performs addition, subtraction, multiplication \n" \
                " Usage:\n"                                         \
                " operations operation x y\n");

    AddCommand("add",&DummyDevice::Add,
                "performs addition of two numbers\n" \
                " Usage:\n"                                         \
                " add x y\n");

    AddCommand("subtract",&DummyDevice::Subtract,
                "performs subtraction of two numbers\n" \
                " Usage:\n"                                         \
                " subtract x y\n");

    AddCommand("multiply",&DummyDevice::Multiply,
                "performs multiplication of two numbers\n" \
                " Usage:\n"                                         \
                " multiply x y\n");
}

CommandReturn::status DummyDevice::Start(std::vector<std::string>,
                                         std::vector<uint64_t>) {
    if (myDummy) {
        printf("dummy already created\n");
        return CommandReturn::OK;
    }
    /*
    try {
        myDummy = new Dummy();
    }
    */
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Operations(std::vector<std::string> strArg,
                                              std::vector<uint64_t> intArg) {
    // strArg = "add", "subtract", or "multiply"
    // intArg = two integers (floats)

    if (!myDummy) {
        printf("dummy not yet created\n");
        return CommandReturn::OK;
    }


    if (strArg.size() != 1) {
        // need 1 string argument (which command to use)
        return CommandReturn::BAD_ARGS;
    }

    if (intArg.size() != 2) {
        // need exactly 2 numbers
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];

    // work out different cases
    if (strArg[0] == "add") {
        myDummy->add(x,y);
    }
    else if (strArg[0] == "subtract") {
        myDummy->subtract(x,y);
    }
    else if (strArg[0] == "multiply") {
        myDummy->multiply(x,y);
    }

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Add(std::vector<std::string> /* strArg */,
                                       std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    myDummy->add(x,y);
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Subtract(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    myDummy->subtract(x,y);
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Multiply(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    myDummy->multiply(x,y);
    return CommandReturn::OK;
}

