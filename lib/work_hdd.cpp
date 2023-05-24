#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include "work_hdd.h"

void Device::create_buffer() // create buffer
{
    std::unique_ptr<char[]> uniqPtrBuffer(new char[buffer_size]); // smart ptr
    buf = uniqPtrBuffer.get();
    for (int i = 0; i < buffer_size; i++) // init buf
    {
        buf[i] = 0;
    }
}

explicit Device::Device(std::string &file_name) // protect open file
{
    open_file(file_name);
}

Device::Device(std::string &file_name, size_t size_data_gib) : Device::Device(file_name)
{
    if (fd == -1) // maybe error
    {
        throw My_error("[ERROR] open file!");
    }
    data_write = size_data_gib * 1024 * 1024 * 1024;                                         // translate Gb in byte
    std::cout << "data byte: " << data_write << " data GiB: " << size_data_gib << std::endl; // show

    create_buffer(); // run create bufer
}

Device::~Device() // clear
{
    if (close(fd) == -1) // maybe error
    {
        std::cout << "[ERROR] close file!" << std::endl;
    }
}

void Device::open_file(std::string &file_name) // open file
{
    fd = open(file_name.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
}

void Device::write_file()
{
    for (; data_write != 0; data_write - buffer_size)
    {
        size_t bytes_to_write = buffer_size;
        for (int bytes_written = 0; bytes_written < bytes_to_write;) // check
        {

            int currently_written = write(fd, buf + bytes_written, bytes_to_write - bytes_written); // write
            if (currently_written == -1)                                                            // maybe error
            {
                throw My_error("[ERROR] write in file!");
            }

            bytes_written += currently_written; // plus count
        }
        data_write -= buffer_size;
    }
}
