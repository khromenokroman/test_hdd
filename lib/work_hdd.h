#pragma once

#include <iostream>

class Device final // not member
{
private:
    int fd;                         // file descriptor
    char *buf = nullptr;            // bufer
    const size_t bufferSize = 4096; // buffer
    size_t dataWrite;                  // size data write

    void openFile();     // open file
    void createBuffer(); // create buf
    void writeFile();    // write in file

public:
    Device(const Device &dev) = delete;     // copy del
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; // = del

    Device(size_t dataWrite); // init
    ~Device();                // clear
};