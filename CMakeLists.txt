cmake_minimum_required(VERSION 3.27)
project(ClassificationTP C)

set(CMAKE_C_STANDARD 23)

add_executable(ClassificationTP main.c
        Split.c
        DecisionTree.c)
