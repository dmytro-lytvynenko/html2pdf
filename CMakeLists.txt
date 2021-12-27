cmake_minimum_required(VERSION 3.14)
project(html2pdf)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(html2pdf src/sources/main.cpp src/sources/process.cpp)

target_include_directories(html2pdf PUBLIC src/headers/ )
target_link_libraries(html2pdf ${Boost_LIBRARIES} pthread)
