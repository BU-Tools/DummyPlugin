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

    AddCommand("addstream",&DummyDevice::AddStream,
                "adds output stream to streams vector\n" \
                " Usage:\n"                                         \
                " addstream stream\n");

    AddCommand("resetstream",&DummyDevice::ResetStream,
                "clears a streams vector\n" \
                " Usage:\n"                                         \
                " resetstream\n");
    
    AddCommand("printtest",&DummyDevice::PrintTest,
                "tests the Print() method\n" \
                " Usage:\n" \
                "printtest\n");
    
    AddCommand("stringtest",&DummyDevice::StringTest,
               "tests r/w on a stringstream\n" \
               " Usage:\n" \
               "stringtest\n");
}

CommandReturn::status DummyDevice::ResetStream(std::vector<std::string> /* strArg */,
                                                std::vector<uint64_t> /* intArg */) {
    
    ResetStreams(debugStreams);
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::AddStream(std::vector<std::string> /* strArg */,
                                             std::vector<uint64_t> /* intArg */) {
    AddOutputStream(&std::cout, debugStreams);
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Start(std::vector<std::string>,
                                         std::vector<uint64_t>) {
    PrintDebug("Hello world %d\n", 1);
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::PrintTest(std::vector<std::string> /*strArg*/,
                                             std::vector<uint64_t> /*intArg*/) {

    PrintDebug("%s : 0x%.8X\n", "test 1", 0xdeadbeef);
    PrintDebug("%s : \n\t%d\n\t0x%.8X\n", "test 2", 100, 0xBAADF00D);
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
        PrintDebug("%f + %f = %f\n", x, y, x+y);
    }
    else if (operation == "subtract") {
        PrintDebug("%f - %f = %f\n", x, y, x-y);
    }
    else if (operation == "multiply") {
        PrintDebug("%f * %f = %f\n", x, y, x*y);
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
    
    PrintDebug("%f + %f = %f\n", x, y, x+y);

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Subtract(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    PrintDebug("%f - %f = %f\n", x, y, x-y);

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Multiply(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    PrintDebug("%f * %f = %f\n", x, y, x*y);

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

    // write to multiple streams:
    std::ostringstream oss;
    AddOutputStream(&oss, stringStreams);
    AddOutputStream(&std::cout, debugStreams);

    for (size_t iName=0; iName<names.size(); iName++) {
        PrintDebug("Writing to stringstream...\n");
        PrintString("%50s: 0x%08X\n", names[iName].c_str(), 0xdeadbeef);
    }

    PrintDebug("Reading from the stringstream:\n");

    for (auto &stream : stringStreams) {
        PrintDebug(stream->str().c_str());
    }

    return CommandReturn::OK;
}

