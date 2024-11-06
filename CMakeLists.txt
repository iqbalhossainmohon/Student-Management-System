cmake_minimum_required(VERSION 3.28)
project(Student_Management_System C)

set(CMAKE_C_STANDARD 17)

add_executable(Student_Management_System main.c
        login.c
        student.c
        login.h
        student.h
        logout.c
        logout.h
        grading.c
        grading.h)
add_executable(login login.c)
add_executable(student student.c)
add_executable(logout logout.c)
