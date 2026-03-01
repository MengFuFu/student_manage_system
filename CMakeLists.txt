cmake_minimum_required(VERSION 3.16)
project(student_manage_system C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-fexec-charset=UTF-8)
add_compile_options(-finput-charset=UTF-8)

add_executable(student_manage_system
        main.c
        account.c
        student_link_list.c
        admin_port.c
        student_port.c
        teacher_port.c
        file_util.c
        safe_stdin.c
)