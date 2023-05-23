#pragma once

#include <iostream>

class Device final // not member
{
private:
    int fd;              // file descriptor
    char *buf = nullptr; // bufer
    size_t bufferSize;   // buffer
    size_t dataWrite = 10737418240;

    void openFile();                      // open file
    void createBuffer(size_t bufferSize); // create buf
    size_t get_fd();                      // return file description
    void writeFile();                     // write in file

public:
    Device(const Device &dev) = delete;     // copy del
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; //= del

    Device(size_t bufferSize);
    ~Device(); // clear
};