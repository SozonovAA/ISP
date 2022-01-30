cmake_minimum_required(VERSION 3.17)
project(FinanceData)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

message(FinanceData)
add_definitions(-DBOOST_ALL_DYN_LINK)

add_library(FinanceData STATIC urlRequests.cpp urlRequests.h alphavintageapi.cpp alphavintageapi.h ihistiricaldata.h historicaldatapresenter.h historicaldatapresenter.cpp)


FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG master
)
FetchContent_GetProperties(curl)
if(NOT curl_POPULATED)
    FetchContent_Populate(curl)
    add_subdirectory(${curl_SOURCE_DIR} PRIVATE ${curlBINARY_DIR})
endif()

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

target_link_libraries(FinanceData nlohmann_json::nlohmann_json)
target_link_libraries(FinanceData libcurl)


if(MINGW)
    target_link_libraries(FinanceData ws2_32)
endif()


