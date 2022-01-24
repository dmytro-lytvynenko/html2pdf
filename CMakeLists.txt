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

add_executable(html2pdf src/main.cpp)
add_library(get_html src/html/sources/get_html.cpp)
add_library(parser src/html/sources/html_parser.cpp)
add_library(converter src/pdf/sources/converter.cpp)
add_library(TreeBuilder src/pdf/tree_builder/sources/tree_builder.cc src/pdf/tree_builder/sources/tree_link_node.cc src/pdf/tree_builder/sources/tree_text_node.cc)
add_library(PDF_helper src/pdf/sources/pdf_helper.cc )

# not sure that is needed
add_dependencies(html2pdf libharu) 
####

add_dependencies(converter libharu)

target_include_directories(html2pdf PUBLIC src/html/headers/ src/pdf/headers/ src/pdf/tree_builder/headers/)
target_include_directories(get_html PUBLIC src/html/headers/ ${CURL_INCLUDE_DIR})
target_include_directories(parser PUBLIC src/html/headers/ ${CURL_INCLUDE_DIR})
target_include_directories(converter PUBLIC src/pdf/headers/ src/pdf/tree_builder/headers/ ${LIBHARU_INCLUDES})
target_include_directories(TreeBuilder PUBLIC src/pdf/tree_builder/headers/ src/pdf/headers/ ${LIBHARU_INCLUDES})
target_include_directories(PDF_helper PUBLIC src/pdf/headers/ )

target_link_libraries(html2pdf converter TreeBuilder ${CURL_LIBRARIES} get_html parser ${LIBHARU_STATIC_LIB} z curl PDF_helper)
