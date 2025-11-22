cmake_minimum_required(VERSION 3.16)
project(CourseWork)

# Увімкнути сучасний стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(team_system
        main.cpp
        src/AuthManager.cpp
        src/ClubManager.cpp
        src/ContractDetails.cpp
        src/ContractedPlayer.cpp
        src/FieldPlayer.cpp
        src/FileManager.cpp
        src/FreeAgent.cpp
        src/Goalkeeper.cpp
        src/InputValidator.cpp
        src/Menu.cpp
        src/Player.cpp
        src/User.cpp
)

target_include_directories(team_system PRIVATE include)

# Попередження компілятора
target_compile_options(team_system PRIVATE -Wall -Wextra -Wpedantic)
