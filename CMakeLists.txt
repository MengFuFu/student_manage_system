cmake_minimum_required(VERSION 3.20)

project(student_manage_system C)

set(CMAKE_C_STANDARD 99)

add_executable(student_manage_system main.c
        link_list.h
        link_list.c
        file_util.c
        file_util.h
        account.c
        account.h
        safe_stdin.h
        student_port.c
        student_port.h
        teacher_port.c
        teacher_port.h
        admin_port.c
        admin_port.h
        safe_stdin.c)