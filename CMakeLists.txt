cmake_minimum_required(VERSION 3.17)
project(search_engine_lin_morton)
set(EXE_NAME search_engine)

foreach (file IN LISTS)
    configure_file(${file} ${file} COPYONLY)
endforeach ()


set(CMAKE_CXX_STANDARD 14)

add_executable(search_engine_lin_morton main.cpp DocParser.cpp DocParser.h AVLTree.cpp AVLTree.h)