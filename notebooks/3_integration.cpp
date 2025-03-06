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
// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
int fib(int x) {
	if (x <= 1) return x;
	return fib(x - 1) + fib(x - 2);
}

// Potenssiin korotus x^4 = x*x*x*x
template<typename T>
T pow(T x, int num) {
	T res = 1.0f;
	for (int i = 0; i < num; ++i) {
		res = res * x;
	}
	return res;
}

// Funktionaalisesti koodattuna:
template<typename T>
T pow2(T x, int num) {
	/*return func::gen<T>(x, [num, ](auto l, auto r) {
		return l * r; 
	}, 1);*/

	return x;
}

// Kertoma funktio:
int factorial(int x) {
	if (x <= 1) return x;
	return x * factorial(x-1);
}
template<typename T>
T exponent(T x, int n) {
	if (n == 0) return 1;
	return exponent(x, n - 1) + (pow(x, n) / factorial(n));
}

template<typename T>
T myexp(T x) {
	return exponent(x, 10);
}


int main() {
	printf("Start app!\n");
	printf("fib(%d) = %d\n", 0, fib(0) );
	printf("fib(%d) = %d\n", 1, fib(1));
	printf("fib(%d) = %d\n", 2, fib(2));
	printf("fib(%d) = %d\n", 3, fib(3));
	printf("fib(%d) = %d\n", 4, fib(4));
	printf("fib(%d) = %d\n", 5, fib(5));
	printf("fib(%d) = %d\n", 6, fib(6));
	printf("pow(%f,%d) = %f\n", 1.0f, 0, pow(1.0f, 0));
	printf("pow(%f,%d) = %f\n", 1.0f, 1, pow(1.0f, 1));
	printf("pow(%f,%d) = %f\n", 1.0f, 2, pow(1.0f, 2));
	printf("pow(%f,%d) = %f\n", 2.0f, 0, pow(2.0f, 0));
	printf("pow(%f,%d) = %f\n", 2.0f, 1, pow(2.0f, 1));
	printf("pow(%f,%d) = %f\n", 2.0f, 2, pow(2.0f, 2));
	printf("pow(%f,%d) = %f\n", 2.0f, 3, pow(2.0f, 3));
	printf("pow(%f,%d) = %f\n", 2.0f, 4, pow(2.0f, 4));
	printf("pow2(%f,%d) = %f\n", 2.0f, 4, pow2(2.0f, 4));

	printf("Value: %d\n", 1 << 0);
	printf("Value: %d\n", 1 << 1);
	printf("Value: %d\n", 1 << 2);
	printf("Value: %d\n", 1 << 3);
	printf("Value: %d\n", 1 << 4);

	printf("5 * 16 = : %d\n", 5 << 4); // bittisiirto on sama, kuin 2:n potenssilla kertominen
	printf("10 * 256 = : %d\n", 10 << 8);


	printf("factorial(%d) = %d\n", 4, factorial(4));
	printf("factorial(%d) = %d\n", 10, factorial(10));
	printf("factorial(%d) = %d\n", 11, factorial(11));
	printf("factorial(%d) = %d\n", 12, factorial(12));
	printf("factorial(%d) = %d\n", 13, factorial(13));
	printf("factorial(%d) = %d\n", 14, factorial(14));
	printf("factorial(%d) = %d\n", 15, factorial(15));
	printf("factorial(%d) = %d\n", 20, factorial(20));

	using namespace mikroplot;
	std::ofstream outFile("t3_submissions.md");
	Window window(800, 800, "Notebook 3 - Numeric Integration");
	// f(x) -> x (y==x)
	auto f1 = [](float x) {
		return x;
	};

	while (false == window.shouldClose()) {		
		window.setScreen(-1, 15, -1, 15);
		window.drawAxis();	
		/*window.drawFunction(f1, 10);
		window.drawFunction([&f1](float x) {
			return derive(x, f1);
		}, 11);*/
		//window.drawFunction(factorial<float>, 11);

		/*window.drawLines({
			{0.0f, float(factorial(0))},
			{1.0f, float(factorial(1))},
			{2.0f, float(factorial(2))},
			{3.0f, float(factorial(3))},
			{4.0f, float(factorial(4))},
			{5.0f, float(factorial(5))},
			{6.0f, float(factorial(6))},
			{7.0f, float(factorial(7))},
		}, 12, 3);*/

		window.drawFunction(expf, 11);
		window.drawFunction(myexp<float>, 12);

		window.update();
	}
	printf("End app!\n");
	return 0;
}
