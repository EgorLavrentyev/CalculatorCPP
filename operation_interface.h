#pragma once
#include <iostream>

//define an abstract interface for operations
class Operation {
public:
	virtual void destroy() = 0; //this function allows DLL to clean memory when the object is no longer needed
	virtual double func(double a, double b) = 0;

	virtual std::string getName() = 0;
	virtual int getPriority() = 0;

	virtual bool isBinary() = 0;
};
