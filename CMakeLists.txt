cmake_minimum_required(VERSION 3.26)
project(DataStructures_Project_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructures_Project_3 main.cpp
        FoodItem.cpp
        FoodItem.h cmake-build-debug/food_data.csv
        functions.cpp
        functions.h)
