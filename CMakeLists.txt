cmake_minimum_required(VERSION 3.0)

project(rumal)

SET(CMAKE_CXX_STANDARD 17)
# SET(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=1 ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS "-ftemplate-depth=100 ${CMAKE_CXX_FLAGS}")

find_package(Boost COMPONENTS regex REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
SET(RUMAL_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

add_library(rumal INTERFACE)
target_include_directories(rumal INTERFACE ${RUMAL_INCLUDE_DIRS})
target_link_libraries(rumal INTERFACE Boost::boost ${BOOST_REGEX_LIBRARY})

if(MSVC)
  target_compile_options(rumal INTERFACE /W4)
else()
  target_compile_options(rumal INTERFACE -Wall -Wextra -pedantic)
endif()

add_subdirectory(examples/)
ENABLE_TESTING()
add_subdirectory(tests/)
