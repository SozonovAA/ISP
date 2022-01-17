cmake_minimum_required(VERSION 3.17)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

message(Utils)
set (json_path https://github.com/nlohmann/json.git)

add_library(Utils STATIC Log.h Log.cpp JsonParser.h JsonParser.cpp Parser.cpp Parser.h)

FetchContent_Declare(
        json
        GIT_REPOSITORY ${json_path}
        GIT_TAG master
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

target_link_libraries(Utils nlohmann_json::nlohmann_json)


target_link_libraries(Utils p7)
if(MINGW)
    target_link_libraries(Utils ws2_32)
endif()


