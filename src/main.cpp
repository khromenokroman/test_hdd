#include<iostream>

#include "../lib/work_hdd.h"

int main()
{
    std::string file_name = "data";
    std::string file_name2 = "data2";
    try
    {
        Device nvme(file_name, 2);
        nvme.write_file();
        system("ls -lh | grep data");
    Device a(file_name2, 2);

    // a = nvme;

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