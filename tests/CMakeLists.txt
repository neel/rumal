cmake_minimum_required(VERSION 3.0)

FIND_PACKAGE(Boost COMPONENTS regex unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(generator generator.cpp)
TARGET_LINK_LIBRARIES(generator ${Boost_LIBRARIES} rumal)

ADD_EXECUTABLE(js js.cpp)
TARGET_LINK_LIBRARIES(js ${Boost_LIBRARIES} rumal)

ENABLE_TESTING()

ADD_TEST(generator generator --report_level=short --log_level=message --show_progress=true)
ADD_TEST(js js --report_level=short --log_level=message --show_progress=true)

