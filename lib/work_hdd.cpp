#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

#include "work_hdd.h"

void Device::createBuffer() // create buffer
{
    std::unique_ptr<char> uniqPtrBuffer(new char(this->bufferSize)); //smart ptr
    this->buf = uniqPtrBuffer.get(); 
    for (int i = 0; i < this->bufferSize; i++) // init buf
    {
        this->buf[i] = 0;
    }
}

Device::Device(size_t dataWrite)
{
    this->dataWrite = dataWrite * 1024 * 1024 * 1024;
    std::cout << "data byte: " << this->dataWrite << " data Gb: " << dataWrite << std::endl;
    openFile();
    if (this->fd != -1)
    {
        createBuffer();
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
