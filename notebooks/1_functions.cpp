#include <stdio.h>
#include<string>
#include<vector>
#include<typeinfo>
#include<functional>
#include <func_util.h>


void func1()
{
	printf("%s\n", __FUNCTION__);
}
namespace myns {
	void func2()
	{
		printf("%s\n", __FUNCTION__);
	}
}
template<typename T>
void print(T val) {
	printf("%s ",   std::to_string(val).c_str());
	//printf("%s: %s", __FUNCTION__, std::to_string(val).c_str());

}
template<typename T>
T sub(T lhs, T rhs) {
	return lhs - rhs;
};

template<typename T>
T add(T lhs, T rhs) {
	// l - (0 - r):
	return sub(lhs, sub(0, rhs));
};

template<typename T, typename... Args>
void print(T value, Args...args) {
	print(value);
	print(std::forward<Args>(args)...);
}





int main() {
	using namespace func;
	printf("-----------------------------------------\n");
	printf("Kutsu funktiotioita func1 ja func2\n");
	func1();
	myns::func2();
	printf("-----------------------------------------\n");
	printf("-----------------------------------------\n");
	printf("Kutsu printtausfunktiota eri tietotyypeille\n");
	print(1.0f); // float
	printf("\n");
	print(1.0); // double
	printf("\n");
	print(1);  // int
	printf("\n");
	printf("-----------------------------------------\n");
	printf("Varying number of arguments\n");
	print(1, 2, 3, 4, 5, 6, 7, 8);
	printf("\n");
	print(10, 12, 23);
	printf("\n");
	printf("-----------------------------------------\n");
	printf("Lambdat: \n");

	// lambda:
	[]() {
		printf("Hello from lambda: %s\n", __FUNCTION__);
	}();

	auto f = []() {
		printf("Hello from lambda: %s\n", __FUNCTION__);
	};
	printf("Lambdan tietotyyppi: %s\n ", typeid(f).name());
	f();
	f();
	// Tämä ei toimi
	// f= []() {};
	printf("-----------------------------------------\n");
	printf("Funktiopointteri/Funktio-osoitin: \n");
	

	void (*func)() = 0;
	func = f;
	func();
	func();
	auto f1 = []() {
		printf("Toinen lambda!\n");
	};
	func = f1;
	func();
	func();

	std::function<void()> myFunction = f; // sij : myFuntioniin f:n
	myFunction();
	std::function<float(float, float)>sum = [](float lhs, float rhs) {
		return lhs + rhs;
	};
	print(sum(2,2));

	std::function<float(float, float)>sub = [](float lhs, float rhs) {
		return lhs + rhs;
	};
	print(sub(2, 2));

	printf("\n------------------------------------\n");
	printf("Genrointifunktio:\n");
	

	gen(10, [](auto n) {
		printf("n=%d\n", int(n));
	});
	auto printIndexValue = [](auto n) {
		printf("n=%d\n", int(n));
	};
	gen(10, printIndexValue);

	printf("\n------------------------------------\n");
	printf("map:(higer order functions\n");
	

	std::vector<int> v1 = { 1,2,3,4 };
	//kasvata jokaista vektorin "v1" elementtiä uhdellä
	// Tallenna tulos vektoriin "y":
	auto y = map(v1, [](size_t i, int x) {
		return x + 1;
		});

	//Tulosta arvot v1:stä
	printf("v1:\n");
	map(v1, [](auto i, auto v) {
		printf("i=%d: %d\n", int(i), v);
		return v;
	});
	printf("\n------------------------------------\n");
	printf("Filter:(higer order functions)\n");

	y = filter(v1, [](auto i, auto v) {
		return v < 3;
	});
	printf("filtered v1 (<3):\n");
	map(y, [](auto i, auto v) {
		printf("i=%d: %d\n", int(i), v);
		return v;
	});
	printf("\n------------------------------------\n");
	printf("Fold:(higer order functions):\n");
	
	printf("folded v1 %d\n", fold(v1, add<int>));

	return 0;
}
