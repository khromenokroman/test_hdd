#pragma once

#include <string>
#include <memory>

class Device final // not member
{
private:
    int fd;                                 // file descriptor
    std::unique_ptr<char[]> buf;            // bufer
    static const size_t buffer_size = 4096; // buffer
    size_t data_write;                      // size data write
    char tmp_file[40];

    void parser_file_name(std::string &file_name); // parser file name -> temp file
    void open_file();                              // open file
    void create_buffer();                          // create buf
    explicit Device(std::string &file_name);       // open file

public:
    Device(std::string &file_name, size_t data_write); // main
    void write_file();                                 // write in file

    ~Device();                                          // clear
    Device &operator=(Device &&dev) noexcept = default; // =move
};

class My_error final : std::exception
{
public:
    explicit My_error(const std::string &&message) noexcept : message{std::move(message)} {}
    const char *what() const noexcept override { return message.c_str(); } // message
private:
    std::string message; // message
};