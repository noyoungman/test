cmake_minimum_required(VERSION 3.14)
project(binary_tree_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Original executable
add_executable(binary_tree binary_tree.cpp)

# Google Test
find_package(GTest REQUIRED)
enable_testing()

add_executable(binary_tree_test binary_tree_test.cpp)
target_link_libraries(binary_tree_test GTest::GTest GTest::Main)

add_test(NAME BinaryTreeTests COMMAND binary_tree_test)
