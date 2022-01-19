cmake_minimum_required(VERSION 3.14)
project(html2pdf)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED) 

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
add_library(get_html src/sources/get_html.cpp)
add_library(converter src/sources/converter.cpp)
add_library(TreeBuilder src/sources/tree_builder/tree_builder.cc src/sources/tree_builder/tree_link_node.cc src/sources/tree_builder/tree_text_node.cc)
add_library(PDF_helper src/sources/pdf_helper.cc )

# not sure that is needed
add_dependencies(html2pdf libharu) 
####

add_dependencies(converter libharu)

target_include_directories(html2pdf PUBLIC src/headers/ )
target_include_directories(get_html PUBLIC src/headers/ ${CURL_INCLUDE_DIR})
target_include_directories(converter PUBLIC src/headers/ ${LIBHARU_INCLUDES})
target_include_directories(TreeBuilder PUBLIC src/headers/ ${LIBHARU_INCLUDES})
target_include_directories(PDF_helper PUBLIC src/headers/ )

target_link_libraries(html2pdf converter TreeBuilder ${CURL_LIBRARIES} get_html ${LIBHARU_STATIC_LIB} z curl PDF_helper)
