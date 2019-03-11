cmake_minimum_required(VERSION 3.11)

project(Program)

#ustaw zbior plików zrodlowych projektu
set(SOURCE_FILES
        src/main.cpp)

#wlacz wskazane pliki do programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})

#Dolacz POBILibrary
target_link_libraries(Program Biblioteka )#${Boost_LIBRARIES})

#dalacz pliki naglowkowe include projektu glownego
target_include_directories(Program PUBLIC include)