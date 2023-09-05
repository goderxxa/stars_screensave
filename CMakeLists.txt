cmake_minimum_required(VERSION 3.23)
project(sfml_space)

set(SOURCE_FILES main.cpp)
add_executable(sfml_space ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(sfml_space sfml-system sfml-window sfml-graphics )