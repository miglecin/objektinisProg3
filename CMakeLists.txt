cmake_minimum_required(VERSION 3.10)

# Nustatome projekto pavadinimą
project(MyVectorProject)

# Nustatome C++ standartą
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Užkrauname Catch2 biblioteką
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Nurodome, kur yra antraščių failai
include_directories(${CMAKE_SOURCE_DIR}/include)

# MyVector biblioteka kaip INTERFACE, nes viskas realizuota .h faile
add_library(MyVector INTERFACE)
target_include_directories(MyVector INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Pagrindinis šaltinio failas
add_executable(VectorApp
    Src/v1.2.cpp
    Src/sparta.cpp
    Src/perskirstymai.cpp
    Src/LaikoMatavimas.cpp
    Src/testRuleOf5.cpp
    Src/versijos1Funkc.cpp
    Src/studentas.cpp
    Src/strategija3.cpp
)

target_link_libraries(VectorApp PRIVATE MyVector)

# Testų programa
add_executable(tests
    Src/catchTests.cpp
)

# Susiejame Catch2 su testų programa
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain MyVector)

# Testų konfigūracija
enable_testing()
add_test(NAME MyVectorTests COMMAND tests)
