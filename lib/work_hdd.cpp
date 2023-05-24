#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include "work_hdd.h"

void Device::create_buffer() // create buffer
{
    std::unique_ptr<char> uniqPtrBuffer(new char[buffer_size]); // smart ptr
    buf = uniqPtrBuffer.get();
    for (int i = 0; i < buffer_size; i++) // init buf
    {
        buf[i] = 0;
    }
}

Device::Device(char *file_name) // protect open file
{
    this->file_name = file_name;
    open_file(this->file_name);
}

Device::Device(char *file_name, size_t data_write) : Device::Device(file_name)
{
    this->data_write = data_write * 1024 * 1024 * 1024;                                         // translate Gb in byte
    std::cout << "data byte: " << this->data_write << " data GiB: " << data_write << std::endl; // show

    create_buffer(); // run create bufer
}

Device::~Device() // clear
{
    close(this->fd);
}

void Device::open_file(char *file_name) // open file
{
    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
    if (fd == -1)
    {
        throw My_error("[ERROR] open file");
    }
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
                throw My_error("[ERROR] write in file");
            }

            bytes_written += currently_written; // plus count
        }
        data_write -= buffer_size;
    }
}
