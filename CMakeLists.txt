cmake_minimum_required(VERSION 3.20)
project(ex4_evyataralcalay C)

set(CMAKE_C_STANDARD 11)

add_executable(ex4_evyataralcalay
        HashSet.c
        Node.c
        Hash.h
        Utils.h
        test_runner.h
        test_runner.c
        tests.c)
