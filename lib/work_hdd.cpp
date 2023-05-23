#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include "work_hdd.h"

void Device::createBuffer() // create buffer
{
    std::unique_ptr<char> uniqPtrBuffer(new char(this->bufferSize)); // smart ptr
    this->buf = uniqPtrBuffer.get();
    for (int i = 0; i < this->bufferSize; i++) // init buf
    {
        this->buf[i] = 0;
    }
}

Device::Device(char *file_name) // protect open file
{
    this->file_name = file_name;
    openFile(this->file_name);
}

Device::Device(char *file_name, size_t dataWrite) : Device::Device(file_name)
{
    this->dataWrite = dataWrite * 1024 * 1024 * 1024;                                        // translate Gb in byte
    std::cout << "data byte: " << this->dataWrite << " data Gb: " << dataWrite << std::endl; // show

    createBuffer(); // run create bufer
    writeFile();    // write data in file
}

Device::~Device() // clear
{
    close(this->fd);
}

void Device::openFile(char *file_name) // open file
{
    this->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
}

void Device::writeFile()
{
    for (; this->dataWrite != 0; this->dataWrite - bufferSize)
    {
        size_t bytesToWrite = bufferSize;
        for (int bytesWritten = 0; bytesWritten < bytesToWrite;) // check
        {

            int currentlyWritten = write(fd, buf + bytesWritten, bytesToWrite - bytesWritten); // write
            if (currentlyWritten == -1)                                                        // maybe error
            {
                std::cout << "[ERROR] Cannnot write file!"
                          << "\n";
            }
            bytesWritten += currentlyWritten; // plus count
        }
        this->dataWrite -= bufferSize;
    }
}
