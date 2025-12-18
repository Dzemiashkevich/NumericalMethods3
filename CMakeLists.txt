cmake_minimum_required(VERSION 3.31)
project(NumericalMethodsLab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(NumericalMethodsLab3 Task2/Task2.cpp
        Methods/CentralRect.h
        Methods/diff.h
        Methods/Trapeze.h
        Methods/Sympson.h
        Methods/GeneralInteg.h
        Methods/Newton_Kotes.h
        Methods/Ature_Coefficients.h
        Methods/GaussKristoff.h
        Methods/GaussLeg.h
        Methods/GaussCheb.h
        Methods/GaussLag.h)
