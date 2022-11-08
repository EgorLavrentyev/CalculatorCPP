
#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <stack>
#include <cmath>
#include <vector>
#include <windows.h>
#include <filesystem>
#include <conio.h>

#include "basic_operations.h";
#include "operation_interface.h"

typedef Operation* (__cdecl* iklass_factory)();

class Calculator {
public:
	Calculator();
	~Calculator();
	void start();
	
private:
	void readDll();
	std::string readExp();
	std::string fixExp(std::string exp);
	std::string createRPN(std::string& exp);
	double calculate(double a, double b, std::string& operation);
	Operation* getOperation(std::string& operation);
	double solveRPN(std::string& exp);

	 std::vector<HINSTANCE> dlls;
	 std::vector<Operation*> operations;

};

