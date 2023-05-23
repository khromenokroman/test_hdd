#pragma once

#include <iostream>

class Device final // not member
{
private:
    int fd;                          // file descriptor
    char *buf = nullptr;             // bufer
    std::string fileName;            // file name
    const size_t SIZE_BUFFER = 4000; // buffer

public:
    Device(const Device &dev) = delete;     // copy del
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; //= del

    Device(char *fileName){}; // open file
    size_t get_fd();          // return file description

    ~Device(){}; // clear
};