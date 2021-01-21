//#include <DummyTextIO/DummyTextIO.hh>
#include <DummyDevice/DummyTextIO.hh>

/*
void DummyTextIO::AddOutputStream(std::unique_ptr<std::ostream> stream) {
    streams.emplace_back(stream);
}
*/

void DummyTextIO::ResetStreams() {
    /*
    for (auto &stream : streams) {
        &stream.get()->flush();
    }
    */
}
