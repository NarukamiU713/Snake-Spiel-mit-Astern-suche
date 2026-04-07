cmake_minimum_required(VERSION 3.20)

project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(snake
    main.cpp
    Food.cpp
    GameSetting.cpp
    Snake.cpp
)

target_include_directories(snake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
