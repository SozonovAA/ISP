cmake_minimum_required(VERSION 3.17)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

message(Utils)

#add_library(Utils STATIC )


#target_link_libraries(Utils p7)
if(MINGW)
    target_link_libraries(Utils ws2_32)
endif()


