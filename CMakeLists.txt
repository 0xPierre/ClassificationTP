cmake_minimum_required(VERSION 3.27)
project(ClassificationTP C)

set(CMAKE_C_STANDARD 23)
file(COPY Datasets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(ClassificationTP main.c
        Split.c
        DecisionTree.c
        Dataset.c
        ForestFileHandler.c
        RandomForest.c
        Tests.c)
target_link_libraries(ClassificationTP m)