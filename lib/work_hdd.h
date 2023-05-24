#pragma once
#include <iostream>

class Device final // not member
{
private:
    int fd;                          // file descriptor
    char *buf = nullptr;             // bufer
    const size_t buffer_size = 4096; // buffer
    size_t data_write;               // size data write

    void open_file(std::string &file_name); // open file
    void create_buffer();                   // create buf
    explicit Device(std::string &file_name);         // open file

public:
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; // = del
    Device(const Device &dev) = delete;     // copy del

    void write_file();                                 // write in file
    Device(std::string &file_name, size_t data_write); // buffer
    ~Device();                                         // clear
};

class My_error final : public std::exception
{
public:
    explicit My_error(const std::string &&message) : message{message} {}
    const char *what() const noexcept override { return message.c_str(); } // message
    My_error(const My_error &&err) = delete;                               // move del
    My_error operator=(My_error &err) = delete;                            // = del
    My_error(const My_error &err) = delete;                                // copy del
private:
    std::string message; // message
};