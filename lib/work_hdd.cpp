#include<iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "work_hdd.h"

size_t Device::get_fd() // return file description
{
    return this->fd;
}

Device::Device(char *fileName)
{
    this->fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
    if (this->fd == -1)                                                                                                    // maybe error
    {
        std::cout << "[ERROR] Cannnot open file!"
                  << "\n";
    }
}

