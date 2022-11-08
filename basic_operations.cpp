#include "basic_operations.h"

Addition::Addition() : name("+"), is_binary(true), priority(2) {}
Addition::~Addition(){
	std::cerr << "MyKlass destructor\n";
}
void Addition::destroy() {};
double Addition::func(double a, double b) {
	return a + b;
}
std::string Addition::getName() {
	return name;
}
int Addition::getPriority() {
	return priority;
}
bool Addition::isBinary() {
	return is_binary;
}

Subtraction::Subtraction() : name("-"), is_binary(true), priority(2) {}
Subtraction::~Subtraction() {
	std::cerr << "MyKlass destructor\n";
}
void Subtraction::destroy() {};
double Subtraction::func(double a, double b) {
	return b - a;
}
std::string Subtraction::getName() {
	return name;
}
int Subtraction::getPriority() {
	return priority;
}
bool Subtraction::isBinary() {
	return is_binary;
}

Multiplication::Multiplication() : name("*"), is_binary(true), priority(3) {}
Multiplication::~Multiplication() {
	std::cerr << "MyKlass destructor\n";
}
void Multiplication::destroy() {};
double Multiplication::func(double a, double b) {
	return a * b;
}
std::string Multiplication::getName() {
	return name;
}
int Multiplication::getPriority() {
	return priority;
}
bool Multiplication::isBinary() {
	return is_binary;
}

Division::Division() : name("/"), is_binary(true), priority(3) {}
Division::~Division() {
	std::cerr << "MyKlass destructor\n";
}
void Division::destroy() {};
double Division::func(double a, double b) {
	if (a == 0.0) {
		throw std::exception("err: division by zero");
	}
	return b / a;
}
std::string Division::getName() {
	return name;
}
int Division::getPriority() {
	return priority;
}
bool Division::isBinary() {
	return is_binary;
}

UnarSub::UnarSub() : name("~"), is_binary(false), priority(5) {}
UnarSub::~UnarSub() {
	std::cerr << "MyKlass destructor\n";
}
void UnarSub::destroy() {};
double UnarSub::func(double a, double b) {
	return b - a;
}
std::string UnarSub::getName() {
	return name;
}
int UnarSub::getPriority() {
	return priority;
}
bool UnarSub::isBinary() {
	return is_binary;
}