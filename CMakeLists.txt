cmake_minimum_required(VERSION 3.30)
project(Sim_Assignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sim_Assignment main.cpp City.cpp Human.cpp Organism.cpp Zombie.cpp Building.cpp)
