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

    AddCommand("resetvector",&DummyDevice::ResetVector,
                "clears streams vector\n" \
                " Usage:\n"                                         \
                " resetvector\n");
    
    AddCommand("printtest",&DummyDevice::PrintTest,
                "tests the Print() method\n" \
                " Usage:\n" \
                "printtest\n");
}

// compiler doesn't support make_unique, work-around (need to fix)
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

CommandReturn::status DummyDevice::ResetVector(std::vector<std::string> /* strArg */,
                                                std::vector<uint64_t> /* intArg */) {
    // at this point, streams *should* have ostreams to print to 
    controller.Print(streams, "resetting streams vector\n");
    // after this, streams will be empty
    ResetStreams();
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::AddStream(std::vector<std::string> strArg,
                                             std::vector<uint64_t> /* intArg */) {
    if (strArg.size() != 1) {
        // add cout stream
        AddOutputStream(make_unique<std::ostream>(std::cout.rdbuf()));
    }
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Start(std::vector<std::string>,
                                         std::vector<uint64_t>) {
    //printf("dummy already created\n");        // replace this with Controller Print()
    // no need to move vector of unique_ptrs, since Print() takes const l-value reference to streams vector
    controller.Print(/*std::move(streams),*/streams, "message from Controller\n");
    // example formatting
    controller.Print(/*std::move(streams),*/streams, "%3d\n", 23);
    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::PrintTest(std::vector<std::string> /*strArg*/,
                                             std::vector<uint64_t> /*intArg*/) {

    // printer only works when passed the values directly. This means that the controller.Print() functionality is flawed
    std::cout << Printer("string test\n");
    std::cout << Printer("decimal test %d\n", 10);
    std::cout << Printer("hex test 0x%08x\n", 0xDEADBEEF);

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
        controller.Print(streams, "%f + %f = %f\n", x, y, myDummy->add(x,y));
    }
    else if (operation == "subtract") {
        controller.Print(streams, "%f - %f = %f\n", x, y, myDummy->subtract(x,y));
    }
    else if (operation == "multiply") {
        controller.Print(streams, "%f * %f = %f\n", x, y, myDummy->multiply(x,y));
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
    
    controller.Print(streams, "%f + %f = %f\n", x, y, myDummy->add(x,y));

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Subtract(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    controller.Print(streams, "%f - %f = %f\n", x, y, myDummy->add(x,y));

    return CommandReturn::OK;
}

CommandReturn::status DummyDevice::Multiply(std::vector<std::string> /* strArg */,
                                            std::vector<uint64_t> intArg) {
    if (intArg.size() != 2) {
        return CommandReturn::BAD_ARGS;
    }

    float x = intArg[0];
    float y = intArg[1];
    
    controller.Print(streams, "%f * %f = %f\n", x, y, myDummy->add(x,y));

    return CommandReturn::OK;
}

