cmake_minimum_required(VERSION 2.8)

project(Community-Game-test)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE catch)

add_executable(${PROJECT_NAME} ${TESTS_DIR})
target_link_libraries(${PROJECT_NAME} Catch)
