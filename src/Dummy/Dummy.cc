#include <Dummy/Dummy.hh>
#include <string>
#include <iostream>

/// constructor 
Dummy::Dummy() {
    std::cout << "Hello World - from Dummy" << std::endl;
}

// deconstructor 
Dummy::~Dummy() {
    std::cout << "object is being destroyed, destructor called" << std::endl;
}

float Dummy::add(float x, float y) {
    float res;
    res = x + y;
    return res;
}

float Dummy::subtract(float x, float y) {
    float res;
    res = x - y;
    return res;
}

float Dummy::multiply(float x, float y) {
    float res;
    res = x * y;
    return res;
}