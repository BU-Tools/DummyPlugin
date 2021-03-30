#include <DummyDevice/DummyDevice.hh>
#include <DummyDevice/Print.hh>

using namespace BUTool;

// vector of strings -> ofstream
DummyDevice::DummyDevice(std::vector<std::string> /* arg */)
  : CommandList<DummyDevice>("Dummy"),
    myDummy(NULL) {
  myDummy = new Dummy();
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
/*
    AddCommand("addstream",&DummyDevice::AddStream,
                "adds output stream to streams vector\n" \
                " Usage:\n"                                         \
                " addstream stream\n");

    AddCommand("resetstream",&DummyDevice::ResetStream,
                "clears a streams vector\n" \
                " Usage:\n"                                         \
                " resetstream 0/1/2\n");
*/
    AddCommand("printtest",&DummyDevice::PrintTest,
                "tests the Print() method\n" \
                " Usage:\n" \
                "printtest\n");
    
    AddCommand("stringtest",&DummyDevice::StringTest,
               "tests r/w on a stringstream\n" \
               " Usage:\n" \
               "stringtest\n");
    
    AddCommand("filetest",&DummyDevice::FileTest,
               " ");
}

/*
CommandReturn::status DummyDevice::ResetStream(std::vector<std::string>,
                                               std::vector<uint64_t> intArg) {
    if (intArg.size() != 1) {
        return CommandReturn::BAD_ARGS;
    }
    // options are INFO, DEBUG, ERROR
    int level = intArg[0];
    switch(level)
    {
        case 0:
            ResetStreams(Level::INFO);
            break;
        case 1:
            ResetStreams(Level::DEBUG);
            break;
        case 2:
            ResetStreams(Level::ERROR);
            break;
        default:
            return CommandReturn::BAD_ARGS;
            break;
    }

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::AddStream(std::vector<std::string>,
                                             std::vector<uint64_t> intArg) {
    if (intArg.size() != 1) {
        return CommandReturn::BAD_ARGS;
    }
    int level = intArg[0];
    switch(level)
    {
        case 0:
            AddOutputStream(Level::INFO, &std::cout);
            break;
        case 1:
            AddOutputStream(Level::DEBUG, &std::cout);
            break;
        case 2:
            AddOutputStream(Level::ERROR, &std::cout);
            break;
        default:
            return CommandReturn::BAD_ARGS;
            break;
    }

    return CommandReturn::OK;
}
*/

CommandReturn::status DummyDevice::Start(std::vector<std::string>,
                                         std::vector<uint64_t>) {
    Print(Level::INFO, "Hello World from %s\n", "dummy");
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::PrintTest(std::vector<std::string> /*strArg*/,
                                             std::vector<uint64_t> /*intArg*/) {
    Print(Level::INFO, "%s : 0x%.8X\n", "test 1", 0xdeadbeef);
    Print(Level::INFO, "%s : \n\t%d\n\t0x%.8X\n", "test 2", 100, 0xBAADF00D);
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Operations(std::vector<std::string> strArg,
                                              std::vector<uint64_t> intArg) {
    // strArg = "add", "subtract", or "multiply"
    // intArg = two integers (floats)
    std::string operation(strArg[0]);
    float x(intArg[1]);
    float y(intArg[2]);

    /* Need to capture the output from the operations using controller.Print() */
    if (operation == "add") {
        Print(Level::INFO, "%f + %f = %f\n", x, y, x+y);
    }
    else if (operation == "subtract") {
        Print(Level::INFO, "%f - %f = %f\n", x, y, x-y);
    }
    else if (operation == "multiply") {
        Print(Level::INFO, "%f * %f = %f\n", x, y, x*y);
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
    
    Print(Level::INFO, "%f + %f = %f\n", x, y, x+y);

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Subtract(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    Print(Level::INFO, "%f - %f = %f\n", x, y, x-y);

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Multiply(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    Print(Level::INFO, "%f * %f = %f\n", x, y, x*y);

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::StringTest(std::vector<std::string>,
                                              std::vector<uint64_t>) {
    // mimicking the behavior of ApolloSMDevice::Read
    // https://github.com/BU-Tools/BUTool/blob/3716389c20e8e8708c02eccf47d74222bf290cf8/src/helpers/register_helper.cc#L242

    std::vector<std::string> names;
    for (int i=0; i<10; i++) {
        names.push_back(std::string("PL_MEM.SCRATCH.WORD_0"+std::to_string(i)));
    }

    // the apollo-herd code would create an ostringstream and pass it via
    // SM->AddOutputStream(Level::level, &oss)
    std::ostringstream oss;
    AddOutputStream(Level::INFO, &oss);

    // this mimics the ipbus-regHelper/uHAL functionality
    for (size_t iName=0; iName<names.size(); iName++) {
        Print(Level::INFO, "%50s: 0x%08X\n", names[iName].c_str(), 0xdeadbeef);
    }

    // the command result would now be captured in the stringstream
    // the stringstream can then be read out on the herd side, since it owns the stringstream
    std::cout << "from stringstream:\n" << oss.str(); 

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::FileTest(std::vector<std::string>, std::vector<uint64_t>) {
    // clear whatever is in the vector (we'll just use INFO vector)
    ResetStreams(Level::INFO);

    // add three streams to INFO level vector
    AddOutputStream(Level::INFO, &std::cout);
    std::ostringstream oss;
    AddOutputStream(Level::INFO, &oss);
    std::ofstream ofs("fileTest.txt", std::ofstream::out);
    AddOutputStream(Level::INFO, &ofs);

    // write something to all streams 
    Print(Level::INFO, "writing to %d %s\n",3,"streams");

    std::cout << "from stringstream: " << oss.str();

    ResetStreams(Level::INFO);

    return CommandReturn::OK;
}
