cmake_minimum_required(VERSION 4.1)
project(FirstLab C)

set(CMAKE_C_STANDARD 17)

add_executable(ui main.c
        headers/UsersStructs.h
        headers/MathVector.h
        headers/FieldInfo.h
        headers/UI.h
        c/MathVector.c
        c/FieldInfo.c
        c/UI.c)

add_executable(tests tests.c
        headers/UsersStructs.h
        headers/MathVector.h
        headers/FieldInfo.h
        c/MathVector.c
        c/FieldInfo.c)

add_compile_options(-Wall -Wextra -Wpedantic)