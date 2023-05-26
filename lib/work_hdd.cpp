#include "work_hdd.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <chrono>
#include <iostream>

#include <memory>

void Device::create_buffer() // create buffer
{
    buf = std::unique_ptr<char[]>(new char[buffer_size]); // smart ptr
}

void Device::parser_file_name(std::string &file_name)
{
    if (file_name.length() > 15) // maybe long name
        throw My_error("[ERROR] the name is too long!!!");
    std::string path = "/tmp/" + file_name + "XXXXXX"; // sum
    for (int i = 0; i < path.length(); i++)
    {
        tmp_file[i] = path[i];
    }
    tmp_file[path.length()] = '\0'; // end string
}

Device::Device(std::string &file_name) // protect open file
{
    parser_file_name(file_name); // pasre
    open_file();                 // open file
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
    unlink(tmp_file);
}

void Device::open_file() // open file
{
    fd = mkstemp(tmp_file);
}

void Device::write_file()
{
    long show_data = data_write; // show info
    auto start = std::chrono::high_resolution_clock::now(); //time start

    for (; data_write != 0; data_write - buffer_size)
    {
        size_t bytes_to_write = buffer_size;
        for (int bytes_written = 0; bytes_written < bytes_to_write;) // check
        {

            int currently_written = write(fd, buf.get() + bytes_written, bytes_to_write - bytes_written); // write
            if (currently_written == -1)                                                                  // maybe error
            {
                throw My_error("[ERROR] write in file!");
            }

            bytes_written += currently_written; // plus count
        }
        data_write -= buffer_size;
    }

    auto stop = std::chrono::high_resolution_clock::now(); //time stop

    std::chrono::duration<float> duration = stop - start; // duration

    std::cout << "Write data: " << show_data << " bytes"
              << "\n"
              << "Time write: " << duration.count() << " sec.\n"
              << "Speed write: " << (show_data / duration.count())/1024/1014 << " Mbytes/sec."
              << "\n"; // show info
}

void foo(Device &&a)
{
    a.write_file();
}
