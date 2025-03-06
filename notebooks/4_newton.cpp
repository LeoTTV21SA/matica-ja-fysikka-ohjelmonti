#include <stdio.h>
#include <mikroplot/window.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include "func_util.h"

template<typename T, typename F>
T derive(T x, F f) {
	const T h = 0.0001f;
	return (f(x+h) - f(x)) / h;
}

template<typename T, typename F>
T newtonsIteration(T x0, F f) {
	return x0 - (f(x0) / derive(x0,  f));
}

float myFunc(float x) {
//	return (-0.5f) + (3.0f * x * x) + (2.0f * x * x * x); // 0.5 + 3*x^2 + 2*x^3
//	return pow(x, 2) + sin(x) - 1;
	return 1.0f * std::exp(-0.1f * x) * sin(5.0f * x);
}


float deriveMyFunc(float x) {
	return derive(x, myFunc);
}
/*float myFunc1(float x) {
	return 0.25*myFunc(x);
}*/
int main() {
	printf("Start app!\n");
	
	using namespace mikroplot;
	Window window(800, 800, "Notebook 4 - Newtons method");
	// f(x) -> x (y==x)
	auto f1 = [](float x) {
		return x;
	};

	std::vector<vec2> lines;

	while (false == window.shouldClose()) {		
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		// Funktio ruudulle
		window.drawFunction(myFunc, 11);
		//window.drawFunction(deriveMyFunc, 12);
		lines.clear();

		if (0) {

			// Alkuarvaus:
			float x = 0.8f; // 0.3666
			x = -1.0f;		// -1.367
			x = -0.8f;		// - 0.50
#if 0

			lines.push_back({ x, myFunc(x) });

			// 1. iteraatio
			x = newtonsIteration(x, myFunc);
			lines.push_back({ x, myFunc(x) });

			// 2. iteraatio
			x = newtonsIteration(x, myFunc);
			lines.push_back({ x, myFunc(x) });

			// 3. iteraatio
			x = newtonsIteration(x, myFunc);
			lines.push_back({ x, myFunc(x) });
#endif
			// Etsi funktion myFunc juuri (funktion nollakohta):
			int i = 0;
			while (fabs(myFunc(x)) > 0.01f) {
				x = newtonsIteration(x, myFunc);
				lines.push_back({ x, myFunc(x) });
				printf("Iter %d, f(x)=%f\n", i, myFunc(x));
				++i;
			}

			printf("Funktion juuri löytyi iteraatiolla %d, x=%f, myFunc(x)=%f\n",
				i, x, myFunc(x));
		} else {
			// Funktion nollkohta:
			// Alkuarvaus:
			float x = 0.0f;
			int i = 0;
			while (fabs(deriveMyFunc(x)) > 0.1f) {
				x = newtonsIteration(x, deriveMyFunc);
				lines.push_back({ x, deriveMyFunc(x) });
				printf("Iter %d, f(x)=%f\n", i, deriveMyFunc(x));
				++i;
			}
			printf("Funktion minimi tai maksimi löytyi iteraatiolla %d, x=%f, myFunc(x)=%f\n",
				i, x, myFunc(x));
		}

		//lines.push_back({ 0, 0 });
		//lines.push_back({ 3, 2 });

		//window.drawLines(lines);
		window.drawPoints(lines, 13, 6);
		//window.drawFunction(myFunc1, 12);
		//window.drawFunction(myexp<float>, 12);

		window.update();
	}
	printf("End app!\n");
	return 0;
}
