#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>

int main(int argc, char *argv[])
{
    const size_t DATA = 10737418240;
    char *buf = nullptr;
    const size_t SIZE_BUFFER = 4000; // buffer
    size_t dataWrite = DATA;

    buf = (char *)malloc(SIZE_BUFFER); // alloc buffer
    if (NULL == buf)                   // maybe error
    {
        std::cout << "[ERROR] System cannot give memory!"
                  << "\n";
        return -1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); // open file
    if (fd == -1)                                                                                                    // maybe error                                                                                                    // maybe error
    {
        std::cout << "[ERROR] Cannnot open file!"
                  << "\n";
        return -1;
    }

    for (int i = 0; i < SIZE_BUFFER; i++) // init buf
    {
        buf[i] = 0;
    }

    auto start = std::chrono::high_resolution_clock::now(); // time start

    for (; dataWrite != 0; dataWrite - SIZE_BUFFER)
    {

        if (dataWrite < SIZE_BUFFER)
        {
            char *buf_new = (char *)malloc(dataWrite); // alloc bufer
            if (NULL == buf_new)                       // maybe error
            {
                std::cout << "[ERROR] System cannot give memory!"
                          << "\n";
                free(buf); // clear
                close(fd);
                return -1;
            }
            for (int i = 0; i < dataWrite; i++) // init buf
            {
                buf_new[i] = 0;
            }

            size_t bytesToWrite = dataWrite;                         // maybe not write
            for (int bytesWritten = 0; bytesWritten < bytesToWrite;) // check
            {

                int currentlyWritten = write(fd, buf + bytesWritten, bytesToWrite - bytesWritten); // write
                if (currentlyWritten == -1)                                                        // maybe error
                {
                    std::cout << "[ERROR] Cannnot write file!"
                              << "\n";
                    return -1;
                }
                bytesWritten += currentlyWritten; // plus count
            }
            dataWrite -= dataWrite;
        }
        else
        {
            size_t bytesToWrite = SIZE_BUFFER;
            for (int bytesWritten = 0; bytesWritten < bytesToWrite;) // check
            {

                int currentlyWritten = write(fd, buf + bytesWritten, bytesToWrite - bytesWritten); // write
                if (currentlyWritten == -1)                                                        // maybe error
                {
                    std::cout << "[ERROR] Cannnot write file!"
                              << "\n";
                    free(buf);
                    close(fd);
                    return -1;
                }
                bytesWritten += currentlyWritten; // plus count
            }
            dataWrite -= SIZE_BUFFER;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now(); // time finish

    std::chrono::duration<float> duration = finish - start; // duration

    std::cout << "Write data: " << DATA << " bytes"
              << "\n"
              << "Time write: " << duration.count() << " sec.\n"
              << "Speed write: " << (DATA / duration.count())/1024/1014 << " Mbytes/sec."
              << "\n"; // show info

    /*clean*/
    free(buf);
    close(fd);
    
}