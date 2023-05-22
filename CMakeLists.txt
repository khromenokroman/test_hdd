cmake_minimum_required(VERSION 3.5)

project(test_speed_hdd)

add_executable(test_speed_hdd
    main.cpp
)
set_target_properties(test_speed_hdd PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)