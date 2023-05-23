cmake_minimum_required(VERSION 3.5)

project(speed_test_hdd)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

add_library(${PROJECT_NAME}_lib SHARED ${PROJECT_SOURCE_DIR/lib/work_hdd.cpp})

#add_library(${PROJECT_NAME}_ll::lib_1 ALIAS ${PROJECT_NAME}_ll)

#target_include_directories(${PROJECT_NAME}_ll PUBLIC ${PROJECT_SOURCE_DIR}/lib_src)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

#target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_ll::lib_1)