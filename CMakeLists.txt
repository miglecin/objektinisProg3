# CMake minimalus reikalavimas
cmake_minimum_required(VERSION 3.10)

# Nustatome projekto pavadinimą
project(MyVectorProject)

# Nustatome C++ standartą
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nurodome, kur yra antraščių failai
include_directories(${CMAKE_SOURCE_DIR}/include)

# Pagrindiniai šaltinio failai
add_executable(VectorApp Src/main.cpp Src/MyVector.cpp)

# Jei turite kitų šaltinių, pridėkite juos čia
# add_executable(VectorApp Src/main.cpp Src/vectorius.cpp)
