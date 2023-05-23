#pragma once

#include <iostream>

class Device final // not member
{
private:
    int fd;              // file descriptor
    char *buf = nullptr; // bufer
    size_t bufferSize = 4096;   // buffer
    int dataWrite;    // size data write

    void openFile();                      // open file
    void createBuffer(size_t bufferSize); // create buf
    size_t get_fd();                      // return file description
    void writeFile();                     // write in file

public:
    Device(const Device &dev) = delete;     // copy del
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; //= del

    Device(size_t dataWrite); // init
    ~Device();                                   // clear
};