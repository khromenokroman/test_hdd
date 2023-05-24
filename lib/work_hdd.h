#pragma once
#include <iostream>

class Device final // not member
{
private:
    int fd;                          // file descriptor
    char *file_name;                 // name file
    char *buf = nullptr;             // bufer
    const size_t buffer_size = 4096; // buffer
    size_t data_write;               // size data write

    void open_file(char *file_name);    // open file
    void create_buffer();               // create buf
    Device(const Device &dev) = delete; // copy del

public:
    Device(const Device &&dev) = delete;    // move del
    Device operator=(Device &dev) = delete; // = del

    void write_file();                          // write in file
    Device(char *file_name);                    // open file
    Device(char *file_name, size_t data_write); // buffer
    ~Device();                                  // clear
};

class My_error final : public std::exception
{
public:
    My_error(const std::string& message): message{message}
    {}
    const char* what() const noexcept override
    {
        return message.c_str();     // получаем из std::string строку const char*
    }
private:
    std::string message;    // сообщение об ошибке
};