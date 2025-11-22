cmake_minimum_required(VERSION 3.16)
project(CourseWork LANGUAGES CXX)

# Вмикаємо C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Джерела
set(SOURCES
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
        main.cpp
)

add_executable(team_system ${SOURCES})

target_include_directories(team_system PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Корисні попередження
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(team_system PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
    target_compile_options(team_system PRIVATE /W4 /permissive-)
endif()
