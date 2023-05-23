#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "work_hdd.h"

size_t Device::get_fd() // return file description
{
    return this->fd;
}

size_t Device::createBuffer(size_t bufferSize) noexcept//create buffer
{
    this->bufferSize = bufferSize;
    this->buf = new char[bufferSize]; // buffer
}

Device::Device(size_t bufferSize)
{
    openFile();
    if(this->fd != -1)
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

Device::~Device() //clear
{
    close(this->fd);
    delete [] this->buf;
}

void Device::openFile() noexcept //openfile
{
    this->fd = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
}

size_t Device::writeFile()
{
    for (int i = 0; i < bufferSize; i++) // init buf
    {
        this->buf[i] = 0;
    }

    for (; this->dataWrite != 0; this->dataWrite - bufferSize)
    {

        if (this->dataWrite < bufferSize)
        {
            // char *buf_new = (char *)malloc(dataWrite); // alloc bufer
            char *buf_new = new char[dataWrite]; // buffer
            if (NULL == buf_new)                 // maybe error
            {
                std::cout << "[ERROR] System cannot give memory!"
                          << "\n";
            }
            for (int i = 0; i < dataWrite; i++) // init buf
            {
                buf_new[i] = 0;
            }

            size_t bytesToWrite = this->dataWrite;                         // maybe not write
            for (int bytesWritten = 0; bytesWritten < bytesToWrite;) // check
            {

                int currentlyWritten = write(this->fd, this->buf + bytesWritten, bytesToWrite - bytesWritten); // write
                if (currentlyWritten == -1)                                                        // maybe error
                {
                    std::cout << "[ERROR] Cannnot write file!"
                              << "\n";
                }
                bytesWritten += currentlyWritten; // plus count
            }
            this->dataWrite -= this->dataWrite;
        }
        else
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
}
