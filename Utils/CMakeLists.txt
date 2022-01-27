cmake_minimum_required(VERSION 3.17)
project(Utils)

set(CMAKE_CXX_STANDARD 20)

message(Utils)
set (json_path https://github.com/nlohmann/json.git)

add_library(Utils STATIC Log.h Log.cpp JsonParser.h JsonParser.cpp Parser.cpp Parser.h datetime.cpp datetime.h)

if(True)
    set(Boost_USE_STATIC_LIBS ON)
    add_definitions(-DBOOST_PYTHON_STATIC_LIB)
endif()
set(Boost_USE_MULTITHREADED ON)

set(boost_COMPONENTS
    atomic chrono container context contract coroutine date_time exception
    filesystem graph headers iostreams json locale log
    log_setup math_c99 program_options random regex serialization
    system thread timer wave wserialization
)

find_package(Boost 1.76.0 COMPONENTS ${boost_COMPONENTS} REQUIRED)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/libs)

message(STATUS "Boost version: ${Boost_VERSION}")
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(FinanceData ${Boost_LIBRARIES})
else()
    message(BOOST NOT FOUND)
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

target_link_libraries(Utils nlohmann_json::nlohmann_json)


target_link_libraries(Utils p7)
if(MINGW)
    target_link_libraries(Utils ws2_32)
endif()


