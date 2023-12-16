cmake_minimum_required(VERSION 3.27)
project(ClassificationTP C)

set(CMAKE_C_STANDARD 23)

add_executable(ClassificationTP src/main.c
        src/Dataset.c
        include/Dataset.h
        src/Split.c
        include/Split.h
        src/DecisionTree.c
        include/DecisionTree.h)
