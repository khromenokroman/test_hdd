#pragma once

#include <iostream>

class Device final // not member
{
private:
    int fd;              // file descriptor
    char *buf = nullptr; // bufer
    size_t bufferSize;   // buffer

public:
    Device(const Device &dev) = delete;     // copy del
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; //= del

    Device(){};      // open file
    size_t get_fd(); // return file description
    void openFile();
    size_t createBuffer(size_t bufferSize);
    ~Device(){}; // clear
};