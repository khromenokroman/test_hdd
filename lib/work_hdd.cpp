#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "work_hdd.h"

size_t Device::get_fd() // return file description
{
    return this->fd;
}

void Device::createBuffer(size_t bufferSize) // create buffer
{
    this->bufferSize = bufferSize;
    this->buf = new char[bufferSize]; // buffer
    for (int i = 0; i < bufferSize; i++) // init buf
    {
        this->buf[i] = 0;
    }
}

Device::Device(size_t dataWrite)
{
    this->dataWrite = dataWrite * 1024 * 1024 * 1024;
    openFile();
    if (this->fd != -1)
    {
        createBuffer(bufferSize);
        if (this->buf != NULL)
        {
            writeFile();
        }
        else
        {
            std::cout << "[ERROR] Cannot create buffer!" << std::endl;
        }
    }
    else
    {
        std::cout << "[ERROR] Cannot open file!" << std::endl;
    }
}

Device::~Device() // clear
{
    close(this->fd);
    delete[] this->buf;
}

void Device::openFile() // openfile
{
    this->fd = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
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
