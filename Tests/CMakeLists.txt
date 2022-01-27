# Задать минимальную версию CMake:
cmake_minimum_required(VERSION 3.0)
project(Gtest)

include(GoogleTestPath.cmake)

if("${GoogleTestPath}" STREQUAL "")
    message(FATAL_ERROR "Specify googletest path into GoogleTestPath variable in the RepositoryPath.cmake")
else()
    message(STATUS "Find googletest path: " ${GoogleTestPath})
endif()
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY ${GoogleTestPath}
        GIT_TAG        main #master
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#set (json_path //gorbunov/GIT/json)
#
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



# Now simply link against gtest or gtest_main as needed. Eg
add_executable(Gtest main_test.cpp urlRequestsTest.cpp LogTest.cpp DateTimeTest.cpp)


target_link_libraries(Gtest gtest gtest_main)
target_link_libraries(Gtest gmock gmock_main)
target_link_libraries(Gtest FinanceData)
target_link_libraries(Gtest Utils)


