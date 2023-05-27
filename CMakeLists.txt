cmake_minimum_required(VERSION 3.24)
project(Projet_C C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_C main.c formes.c formes.h Shape.c Shape.h id.c id.h Menu.c Menu.h area.c area.h pixels.c pixels.h commands.c commands.h)
