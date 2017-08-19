cmake_minimum_required(VERSION 3.6)
project(mcu_test)

set(CMAKE_C_STANDARD 99)

add_custom_target(mcu_test ALL COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
