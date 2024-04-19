cmake_minimum_required(VERSION 3.23)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManager main.cpp Password.cpp Encryption.cpp Encryption.hpp Password.hpp SaveReadFile.cpp SaveReadFile.hpp)
