cmake_minimum_required(VERSION 3.0)

FIND_PACKAGE(Boost COMPONENTS regex unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(aql aql.cpp)
TARGET_LINK_LIBRARIES(aql ${Boost_LIBRARIES} rumal)

ENABLE_TESTING()

ADD_TEST(aql aql --report_level=short --log_level=message --show_progress=true)
