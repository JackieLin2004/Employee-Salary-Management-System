cmake_minimum_required(VERSION 3.27)
project(EmployeeSalaryManagementSystem)

set(CMAKE_CXX_STANDARD 23)

add_executable(EmployeeSalaryManagementSystem main.cpp
        CEmployee.cpp
        CEmployee.h
        BDay.h
        CManager.cpp
        CManager.h
        CSales.cpp
        CSales.h
        CMgr.cpp
        CMgr.h
        CWage.cpp
        CWage.h
        system.cpp
        system.h
)
