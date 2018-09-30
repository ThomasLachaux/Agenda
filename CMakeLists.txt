cmake_minimum_required(VERSION 3.12)
project(Agenda C)

set(CMAKE_C_STANDARD 99)

add_executable(Agenda main.c tools.c tools.h administration.c administration.h agenda.c agenda.h)