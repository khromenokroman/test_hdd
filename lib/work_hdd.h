#pragma once

class Device final // not member
{
private:
    int fd;                         // file descriptor
    char *file_name;                // name file
    char *buf = nullptr;            // bufer
    const size_t bufferSize = 4096; // buffer
    size_t dataWrite;               // size data write

    void openFile(char *file_name); // open file
    void createBuffer();            // create buf
    void writeFile();               // write in file

public:
    Device(const Device &dev) = delete;     // copy del
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; // = del

    Device(char *file_name);                   // open file
    Device(char *file_name, size_t dataWrite); // buffer
    ~Device();                                 // clear
};