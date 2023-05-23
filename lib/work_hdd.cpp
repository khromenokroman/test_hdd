#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "work_hdd.h"

size_t Device::get_fd() // return file description
{
    return this->fd;
}

size_t Device::createBuffer(size_t bufferSize)
{
    this->bufferSize = bufferSize;
    this->buf = new char[bufferSize]; // buffer
}

Device::Device()
{
}

void Device::openFile() noexcept
{
    this->fd = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
}
