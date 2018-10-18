cmake_minimum_required(VERSION 3.12)
project(Agenda C)

set(CMAKE_C_STANDARD 99)

add_executable(Agenda src/main.c src/tools.c src/tools.h src/administration.c src/administration.h src/agenda.c src/agenda.h)