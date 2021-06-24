cmake_minimum_required(VERSION 3.19)
project(ValidateISBN)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "B:\\Coding Languages\\C++\\Standard C++\\Boost Library\\boost_1_76_0")
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

add_executable(ValidateISBN main.cpp)
target_link_libraries(ValidateISBN ${Boost_LIBRARIES})