cmake_minimum_required(VERSION 3.11)

#Parametry konfiguracyjne cmake
set(CMAKE_CXX_COMPILER g++)#wymaga by g++ był na ścieżce
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Profil debug i maksymalny poziom debug info g3 oraz format debug info na dwarf-4 (musi być gdb w wersji 7)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")

project(POBIProject)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
set(CMAKE_VERBOSE_MAKEFILE TRUE) 

add_subdirectory(biblioteka)
add_subdirectory(program)

enable_testing()