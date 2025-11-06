#include <iostream>
#include "runners.h"

int main()
{
	char taskNum, fNum;
	double a, b;
	int N;
	unsigned m, n;
	while (true) {
		std::cout << "Enter the task number:"
			<< "\n1 - calculate integral and auto adjust number of splits."
			<< "\n2 - calculate integral with specified number of splits."
			<< "\n3 - calculate integrals."
			<< "\nAny - Exit.\n";
		
		std::cin >> taskNum;
		switch (taskNum) {
		case '1': 
			std::cout << "Choose the function for integration:"
				<< "\n1 - sin(x)"
				<< "\n2 - e^x"
				<< "\n3 - x^4 + 3*x^2 - 2x + 1\n";
			std::cin >> fNum;
			std::cout << "Enter the integration range [a, b]: "; std::cin >> a >> b;
			compareQuadratures(a, b, fNum);
			break;

		case '2':
			std::cout << "Choose the function for integration:"
				<< "\n1 - cos(1000x)"
				<< "\n2 - e ^ -1000x"
				<< "\n3 - 1 / sqrt(1 - x ^ 2)\n";
			std::cin >> fNum;
			std::cout << "Enter the integration range [a, b]: "; std::cin >> a >> b;
			std::cout << "Enter the number of splits N: "; std::cin >> N;
			compareQuadraturesN(a, b, N, fNum);
			break;

		case '3':
			std::cout << "Enter the number of splits N: "; std::cin >> N;
			calcIntegrals(N);
			break;

		default: std::cout << "\n\n\n\nBye."; return 0;
		}
		std::cout << "\n\n";
	}
	return 0;
}
