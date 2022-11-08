# CMakeList.txt : CMake project for CalculatorCPP, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CalculatorCPP")

# Add source to this project's executable.
add_executable (CalculatorCPP "main.cpp" "Calculator.cpp" "Calculator.h"  "operation_interface.h" "basic_operations.cpp" "basic_operations.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CalculatorCPP PROPERTY CXX_STANDARD 20)
endif()
