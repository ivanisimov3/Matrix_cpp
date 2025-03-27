cmake_minimum_required(VERSION 3.28)
project(MatrixLab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix3 main.cpp
        Symbol.h
        Line.h
        AppManager.h
        Service.h
        Symbol.cpp
        Service.cpp
        Line.cpp
        AppManager.cpp
        Figure.cpp
        Figure.h
        Explosion.cpp
        Explosion.h)
