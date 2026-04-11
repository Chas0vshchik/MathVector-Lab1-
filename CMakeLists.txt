cmake_minimum_required(VERSION 4.1)
project(FirstLab C)

set(CMAKE_C_STANDARD 17)

add_executable(FirstLab main.c
        headers/UsersStructs.h
        headers/MathVector.h
        c/MathVector.c
        c/FieldInfo.c
        headers/FieldInfo.h
        headers/UI.h
        c/UI.c
        tests.c)
