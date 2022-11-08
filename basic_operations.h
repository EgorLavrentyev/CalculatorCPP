#pragma once
#include "operation_interface.h"
#include <iostream>

class Addition : public Operation {
public:
	Addition();
	~Addition();
	void destroy();
	double func(double a, double b);

	std::string getName();
	int getPriority();

	bool isBinary();
private:
	std::string name;
	bool is_binary;
	int priority;
};

class Subtraction : public Operation {
public:
	Subtraction();
	~Subtraction();
	void destroy();
	double func(double a, double b);

	std::string getName();
	int getPriority();

	bool isBinary();
private:
	std::string name;
	bool is_binary;
	int priority;
};

class Multiplication : public Operation {
public:
	Multiplication();
	~Multiplication();
	void destroy();
	double func(double a, double b);

	std::string getName();
	int getPriority();

	bool isBinary();
private:
	std::string name;
	bool is_binary;
	int priority;
};

class Division : public Operation {
public:
	Division();
	~Division();
	void destroy();
	double func(double a, double b);

	std::string getName();
	int getPriority();

	bool isBinary();
private:
	std::string name;
	bool is_binary;
	int priority;
};

class UnarSub : public Operation {
public:
	UnarSub();
	~UnarSub();
	void destroy();
	double func(double a, double b);

	std::string getName();
	int getPriority();

	bool isBinary();
private:
	std::string name;
	bool is_binary;
	int priority;
};