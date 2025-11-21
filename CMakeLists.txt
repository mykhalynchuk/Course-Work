cmake_minimum_required(VERSION 4.0)
project(CourseWork)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(team_system
        main.cpp
        src/Player.cpp
        src/ContractedPlayer.cpp
        include/ContractedPlayer.h
        include/Player.h
        include/AuthManager.h
        include/ClubManager.h
        include/ContractDetails.h
        include/ContractedPlayer.h
        include/FieldPlayer.h
        include/FileManager.h
        include/FreeAgent.h
        include/Goalkeepeer.h
        include/IFileHandler.h
        include/InputValidator.h
        include/Menu.h
        include/Player.h
        include/User.h
        include/Utils.h
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

target_compile_options(team_system PRIVATE -Wall -Wextra -Wpedantic)