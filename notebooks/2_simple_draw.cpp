#include<stdio.h>
#include<mikroplot/window.h>
#include <fstream>
#include <iostream>
#include <math.h>

int main() {
	using namespace mikroplot;
	Window window(800, 800, "Notebook 2- Siple drw");
	std::ofstream outFile("t1_submissions.md");
	auto f1 = [](float x) {
		return x;
	};
	auto f2 = [](float x) {
		return 2*x;
	};
	auto f3 = [](float x) {
		return x* x; // x^2
	};
	auto f4 = [](float x) {
		return x * x * x; // x^3
	};	
	auto f5 = [](float x) {
		return 2 *x * x * x+5*x*x+6*x+2*sin(x); 
	};
	auto f6 = [](float x) {
		return cos(x);
	};
	auto f7 = [](float x) {
		return exp(x);
	};
	auto f8 = [](float x) {
		return log(x);
	};
	auto f9 = [](float x) {
		return sqrt(x);
	};
	auto f10 = [](float x) {
		return sin(x) * cos(x);
	};
	auto f11 = [](float x) {
		return 3 * 2 * sin(x) * 1 * cos(x);
	};
	auto f12 = [](float x) {
		return 2.3 * sin(x) * 1.2 * cos(x);
	};
	auto f13 = [](float x) {
		return 2.3 * sin(x) + 1.2 * cos(x);
	};
	auto f14 = [](float x) {
		return pow(x, x);
	};
	auto f15 = [](float x) {
		return 2 * x * x;
	};
	auto f16 = [](float x) {
		return pow(sin(x), 2);
	};
	auto f17 = [](float x) {
		return tan(x);
	};
	auto f18 = [](float x) {
		return exp(-x);
	};
	auto f19 = [](float x) {
		return log10(x);
	};
	auto f20 = [](float x) {
		return 1 / x;
	};





	int funcNumber = 0;
	while (false==window.shouldClose()) {
	//	window.setScreen(-5, 5, - 5, 5);

	//Nm ei toimi kaikilla koneilla nkjn...-
	//	window.drawAxis();
	//	window.drawFunction(f1, 10);
	//	window.drawFunction(f2, 11);
	//	window.drawFunction(f3, 12);

		window.setScreen(-5, 5, -5, 5);
		window.drawAxis();
		
		if (funcNumber == 0) window.drawFunction(f1, 10);
		if (funcNumber == 1) window.drawFunction(f2, 11);
		if (funcNumber == 2) window.drawFunction(f3, 12);
		if (funcNumber == 3) window.drawFunction(f4, 13);
		if (funcNumber == 4) window.drawFunction(f5, 14);
		if (funcNumber == 5) window.drawFunction(f6, 15);
		if (funcNumber == 6) window.drawFunction(f7, 16);
		if (funcNumber == 7) window.drawFunction(f8, 17);
		if (funcNumber == 8) window.drawFunction(f9, 18);
		if (funcNumber == 9) window.drawFunction(f10, 19);
		if (funcNumber == 10) window.drawFunction(f11, 20);
		if (funcNumber == 11) window.drawFunction(f12, 10);
		if (funcNumber == 12) window.drawFunction(f13, 11);
		if (funcNumber == 13) window.drawFunction(f14, 12);
		if (funcNumber == 14) window.drawFunction(f15, 13);
		if (funcNumber == 15) window.drawFunction(f16, 14);
		if (funcNumber == 16) window.drawFunction(f17, 15);
		if (funcNumber == 17) window.drawFunction(f18, 16);
		if (funcNumber == 18) window.drawFunction(f19, 17);
		if (funcNumber == 19) window.drawFunction(f20, 18);

		outFile << "# Tehtava " << funcNumber << std::endl;
		outFile << std::endl;
		outFile << "Kuvakaappaus alla:" << std::endl;
		outFile << std::endl;
		outFile << "![alt text](screenshot" + std::to_string(funcNumber) + ".png \"Title Text\"){width=400px height=400px}" << std::endl;
		outFile << std::endl;

		window.update();
		window.screenshot("screenshot" + std::to_string(funcNumber) + ".png");


		// Update funcNumber: 0 <= funcNumber < 4
		++funcNumber;
		if (funcNumber >= 20) {
			funcNumber = 0;
			break;
		}
	
	}
	window.update();
	
	printf("End app\n");
	return 0;
}
