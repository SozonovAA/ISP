cmake_minimum_required(VERSION 3.10)
project(ISP VERSION 1.0.1)
message(Main)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(FinanceData)
add_subdirectory(Graphics)
add_subdirectory(TableRead)

add_subdirectory(Tests)
