cmake_minimum_required(VERSION 3.23.2)
project(DataStructures_Project_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(SnackATTACK main.cpp FoodItem.cpp FoodItem.h
        cmake-build-debug/food_data.csv)
