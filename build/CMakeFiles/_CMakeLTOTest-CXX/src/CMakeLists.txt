cmake_minimum_required(VERSION "4.1.0-rc2")
project("lto-test" LANGUAGES CXX)

cmake_policy(SET CMP0069 NEW)

add_library(foo foo.cpp)
add_executable(boo main.cpp)
target_link_libraries(boo PUBLIC foo)
