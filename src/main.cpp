#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "../lib/work_hdd.h"

int main()
{
    try
    {
        Device nvme("data", 2);
        nvme.write_file();
    }
    catch (const char *ex)
    {
        std::cout << ex << "\n";
    }
}