cmake_minimum_required(VERSION 3.6)
project(msp430f5529_projects)

set(CMAKE_C_STANDARD 99)

add_custom_target(msp430f5529_projects ALL COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
