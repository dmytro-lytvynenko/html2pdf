cmake_minimum_required(VERSION 3.14)
project(html2pdf)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# fetching and building LibHaru
include(ExternalProject)
ExternalProject_Add(
  libharu
  GIT_REPOSITORY https://github.com/libharu/libharu.git
  GIT_TAG        d84867ebf9f3de6afd661d2cdaff102457fbc371
  CMAKE_ARGS -DLIBHPDF_SHARED=OFF -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
  # building static lib & installing into binary dir
)

set(LIBHARU_STATIC_LIB "${CMAKE_BINARY_DIR}/lib/libhpdfs.a")
set(LIBHARU_INCLUDES "${CMAKE_BINARY_DIR}/include")

# 

add_executable(html2pdf src/sources/main.cpp)
add_library(process src/sources/process.cpp)
add_library(converter src/sources/converter.cpp)

target_include_directories(html2pdf PUBLIC src/headers/ )
target_include_directories(process PUBLIC src/headers/ )
target_include_directories(converter PUBLIC src/headers/ ${LIBHARU_INCLUDES})

target_link_libraries(html2pdf converter ${Boost_LIBRARIES} process ${LIBHARU_STATIC_LIB} pthread z)
