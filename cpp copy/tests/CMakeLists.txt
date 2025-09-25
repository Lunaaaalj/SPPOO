add_subdirectory(tests)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES test_main.cpp)

add_executable(runTests ${TEST_SOURCES})
target_link_libraries(runTests GTest::GTest GTest::Main)

add_test(NAME runTests COMMAND runTests)