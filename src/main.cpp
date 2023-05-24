#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "../lib/work_hdd.h"

int main()
{
    std::string file_name = "data";
    try
    {
        Device nvme(file_name, 2);
        nvme.write_file();
        system("ls -lh | grep data");
    }
    catch (My_error &ex)
    {
        std::cout << ex.what() << "\n";
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << "\n";
    }
}