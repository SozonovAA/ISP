cmake_minimum_required(VERSION 3.17)
project(TableRead)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

message(TableRead)

#add_library(TableRead STATIC )

#include(BoostRootPath.cmake)
#if(True)
#    set(Boost_USE_STATIC_LIBS ON)
#    set(Boost_USE_STATIC_RUNTIME ON)
#    add_definitions(-DBOOST_PYTHON_STATIC_LIB)
#endif()
#set(Boost_USE_MULTITHREADED ON)
#
#find_package(Boost 1.76.0)
#message(STATUS "Boost version: ${Boost_VERSION}")
#
#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    target_link_libraries(Interconnection ${Boost_LIBRARIES})
#else()
#    message(BOOST NOT FOUND)
#endif()

#FetchContent_Declare(
#        json
#        GIT_REPOSITORY ${json_path}
#        GIT_TAG master
#)
#FetchContent_GetProperties(json)
#if(NOT json_POPULATED)
#    FetchContent_Populate(json)
#    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
#endif()
#target_link_libraries(FinanceData PRIVATE nlohmann_json::nlohmann_json)


if(MINGW)
    target_link_libraries(FinanceData PRIVATE ws2_32)
endif()


