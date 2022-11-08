#include "Calculator.h"

using namespace std;

int main()
{
	Calculator calc;
	try {
		calc.start();
	}
	catch (std::exception& ex)
	{
		printf("Exception: %s\n", ex.what());
	}
	return 0;
}