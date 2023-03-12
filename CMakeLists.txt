cmake_minimum_required(VERSION 3.25)

project(exploit)

# add_library(utils SHARED utils.c)

add_executable(${CMAKE_PROJECT_NAME} main.c utils.c)

target_link_libraries(${CMAKE_PROJECT_NAME} -static)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} command adb push ${CMAKE_PROJECT_NAME} /data/local/tmp)




