
#include "Calculator.h"

typedef Operation* (__cdecl* iklass_factory)();

Calculator::Calculator()
{
	operations.push_back(new Addition);
	operations.push_back(new Subtraction);
	operations.push_back(new Multiplication);
	operations.push_back(new Division);
	operations.push_back(new UnarSub);
}

Calculator::~Calculator()
{
	for (auto& op : operations) {
		delete op;
	}

	for (auto& dll : dlls) {
		FreeLibrary(dll);
	}
}

void Calculator::readDll()
{
	const std::string pluginsDir = "plugins";
	const std::filesystem::path plugins{ pluginsDir };
	std::cout << "Special operations:" << " ";
	if (std::filesystem::is_directory(plugins))
	{
		for (auto const& file : std::filesystem::directory_iterator{ plugins })
		{
			HINSTANCE dll_handle = ::LoadLibraryA(file.path().generic_string().c_str());
			if (!dll_handle) {
				std::cerr << "Unable to load DLL!\n";
				return;
			}
			iklass_factory factory_func = reinterpret_cast<iklass_factory>(::GetProcAddress(dll_handle, "create_klass"));
			if (!factory_func) {
				std::cerr << "Unable to load create_klass from DLL!\n";
				::FreeLibrary(dll_handle);
				return;
			}

			Operation* instance = factory_func();

			operations.push_back(instance);
			dlls.push_back(dll_handle);
			std::cout << instance->getName() << " ";
		}
	}
}

std::string Calculator::readExp()
{
	std::cout << "Enter an expression (type q to quit): ";
	std::string exp;
	std::getline(std::cin, exp);
	return exp;
}

std::string Calculator::fixExp(std::string exp)
{
	std::string fixed_exp;
	std::string cur = "";
	for (int i = 0, k = 0; i < exp.size(); ++i) {
		cur.push_back(exp[i]);
		if (getOperation(cur) || exp[i] == '(' || exp[i] == ')') {
			if (i > 0 && fixed_exp[k - 1] != ' ' || (i > 0 && exp[i - 1] != ' ')) {
				fixed_exp += ' ' + cur + ' ';
				k += 3;
			}
			else {
				fixed_exp += cur + ' ';
				k += 2;
			}
		}
		else if (exp[i] != ' ') {
			fixed_exp.push_back(exp[i]);
			k++;
		}
		cur = "";
	}
	return fixed_exp;
}

std::string Calculator::createRPN(std::string& exp)
{
	std::stack <std::string> stack;
	std::string RPN_string = "";
	std::stringstream s(exp);
	std::string symb;
	std::string prev = "";
	while (s >> symb) {
		if (Operation* op = getOperation(symb)) {
			if (op->getName() == "-" && (prev == "" || getOperation(prev) || prev == "(")) {
				symb = "~";
				op = getOperation(symb);
			}
			if (stack.empty()) {
				stack.push(symb);
			}
			else {
				while (!stack.empty() && getOperation(stack.top()) && getOperation(stack.top())->getPriority() >= op->getPriority()) {
					RPN_string += ' ' + stack.top();
					stack.pop();
				}
				stack.push(symb);
			}
		}
		else if (symb == "(") {
			stack.push(symb);
		}
		else if (symb == ")") {
			while (stack.top() != "(") {
				RPN_string += ' ' + stack.top();
				stack.pop();
			}
			stack.pop();
		}
		else {
			if (RPN_string == "") {
				RPN_string += symb;
			}
			else {
				RPN_string += ' ' + symb;
			}
		}
		prev = symb;
	}
	while (!stack.empty()) {
		RPN_string += ' ' + stack.top();
		stack.pop();
	}
	return RPN_string;
}

double Calculator::calculate(double a, double b, std::string& operation)
{
	if (Operation* op = getOperation(operation)) {
		return op->func(a, b);
	}
}

double Calculator::solveRPN(std::string& exp)
{
	std::stack <std::string> stack;
	std::stringstream s(exp);
	std::string word;
	while (s >> word) {
		if (Operation* op = getOperation(word)) {
			if (op->isBinary()) {
				if (stack.empty()) {
					throw std::exception("error: Incorrect input");
				}
				double a = stod(stack.top());
				stack.pop();
				if (stack.empty()) {
					throw std::exception("error: Incorrect input");
				}
				double b = stod(stack.top());
				stack.pop();
				stack.push(std::to_string(calculate(a, b, word)));
			}
			else {
				if (stack.empty()) {
					throw std::exception("error: Incorrect input");
				}
				double a = stod(stack.top());
				stack.pop();
				stack.push(std::to_string(calculate(a, 0, word)));
			}
		}
		else {
			stack.push(word);
		}
	}
	return stod(stack.top());
}

Operation* Calculator::getOperation(std::string& operation)
{
	for (auto& op : operations) {
		if (op->getName() == operation) {
			return op;
		}
	}
	return nullptr;
}

void Calculator::start()
{
	readDll();
	std::cout << "\nAll available operations: ";
	for (auto& op : operations) {
		std::cout << op->getName() << "  ";
	}
	std::cout << "\n------------------------------------------------------------------\n";
	std::string exp = readExp();
	while (exp != "q") {
		exp = fixExp(exp);
		std::string RPN = createRPN(exp);
		std::cout << "RPN: " << RPN << std::endl;
		double answer = solveRPN(RPN);
		std::cout << "Ans: " << answer << "\n------------------------------------------------------------------\n";
		exp = readExp();
	}
}