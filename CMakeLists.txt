cmake_minimum_required(VERSION 3.0)

project(rumal)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=1 ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS "-ftemplate-backtrace-limit=0 ${CMAKE_CXX_FLAGS}")

find_package(Boost COMPONENTS regex REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
SET(RUMAL_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

add_library(rumal INTERFACE)
target_include_directories(rumal INTERFACE ${RUMAL_INCLUDE_DIRS})
target_link_libraries(rumal INTERFACE Boost::boost ${BOOST_REGEX_LIBRARY})

add_subdirectory(examples/)
ENABLE_TESTING()
add_subdirectory(tests/)
