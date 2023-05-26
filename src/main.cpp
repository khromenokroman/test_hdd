#include<iostream>

#include "../lib/work_hdd.h"

int main()
{
    std::string file_name = "test_ssd";
    try
    {
        Device nvme(file_name, 2);
        nvme.write_file();

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