cmake_minimum_required(VERSION 3.27)
project(ClassificationTP C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
file(COPY Datasets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(ClassificationTP ClassificationTP/main.c
        ClassificationTP/Dataset.c
        ClassificationTP/DecisionTree.c
        ClassificationTP/ForestFileHandler.c
        ClassificationTP/Interface.c
        ClassificationTP/RandomForest.c
        ClassificationTP/Split.c
        ClassificationTP/Tests.c
)
target_link_libraries(ClassificationTP m SDL2)