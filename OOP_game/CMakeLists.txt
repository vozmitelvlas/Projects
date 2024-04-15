set(CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCES
    buffer.h
    ITVSet.h
    MainWindow.h
    MainWindow.cpp
    TVSet.h
    TVSet.cpp
)
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(build)


add_executable(build ./OBJ/main.cpp ./OBJ/Controller.cpp ./OBJ/CommandReader.cpp ./OBJ/PrintField.cpp ./OBJ/Field.cpp ./OBJ/Cell.cpp ./OBJ/Player.cpp ./Events/Event_Win.cpp ./Events/Event_Hp.cpp ./Events/Event_Enemy.cpp ./Events/Event_Damage.cpp ./Events/Event_Arm.cpp)
