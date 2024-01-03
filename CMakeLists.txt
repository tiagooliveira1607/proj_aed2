cmake_minimum_required(VERSION 3.22)
project(proj_aed2)

set(CMAKE_CXX_STANDARD 17)

add_executable(proj_aed2 main.cpp
        Data.cpp
        Data.h
        Airline.cpp
        Airline.h
        Graph.h
        Graph.cpp
        Menu.cpp
        Menu.h
        Application.cpp
        Application.h
        Application.h)

