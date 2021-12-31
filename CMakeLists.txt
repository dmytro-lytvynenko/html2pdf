cmake_minimum_required(VERSION 3.14)
project(html2pdf)

set(CMAKE_CXX_STANDARD 14)
set(CURL_LIBRARY "-lcurl") 

find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

add_executable(html2pdf src/sources/main.cpp src/sources/process.cpp)

target_include_directories(html2pdf PUBLIC src/headers/ )
target_link_libraries(html2pdf ${CURL_LIBRARIES})
