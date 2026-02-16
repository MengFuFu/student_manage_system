cmake_minimum_required(VERSION 3.20)

project(student_manage_system C)

set(CMAKE_C_STANDARD 99)

add_executable(student_manage_system main.c
        link_list.h
        link_list.c
        student_sys.h
        student_sys.c
        file_util.c
        file_util.h
        user.c
        user.h)