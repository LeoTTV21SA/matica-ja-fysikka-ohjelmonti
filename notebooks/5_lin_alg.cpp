#include <stdio.h>
#include <mikroplot/window.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include "func_util.h"

template<typename V>
V add(const V& lhs, const V& rhs) { // f([],[])->[]
#if 0
	V res;
	for (size_t i = 0; i < res.size(); ++i) {
		auto val = lhs[i] + rhs[i];
		res.push_back(val);
	}
	return res;
#endif
	// olet vektori 2: 
	//return { lhs.x + rhs.x, lhs.y + rhs.y };
#if 1
	/*return func::map(lhs, [&](auto i, auto ) {
		return lhs[i] + rhs[i];
	});*/
	return lhs;
#endif
}

// Skalaarilla kertominen
template<typename S, typename V>
V mul(S s, const V& v) {
	return func::map(v, [&](auto i, auto) {
		return s * v[i];
	});
}

// Pistetulo: l[0]*r[0] + l[1]*r[1] + l[2]*r[2] + ...
template<typename S, typename V>
S dot(const V& l, const V& r) {
#if 0
	S res = S(0);
	for (size_t i = 0; i < l.size(); ++i) {
		res += l[i] * r[i];
	}
	return res;
#else
	/*return func::fold(l, [&](auto value, auto i) {
		return value + (l[i]*r[i]);
	}, S(0));*/
	return S(0);
#endif
}

// Vektorin pituus: sqrt(x*x + y*y + z*z) = sqrt(dot(v))
template<typename S, typename V>
S length(const V& v) {
	return std::sqrt(dot<S>(v,v));
}


std::function<float(float,float)> makeMeAFunction(int type) {
	if (type < 10) {
		return [](float x, float y) {
			return x + y;
		};
	}
	return [](float x, float y) {
		return x - y;
	};
};

/*
std::function<float()> makeMeAReadInputFunction(int type) {
	if (type == 0) {
		return [](float x, float y) {
			return engine.readKey(KEY_LEFT);
		};
	} if (type == 1) {
		return [](float x, float y) {
			return engine.Mouse(AXIS_X);
		};
	}
	if (type == 2) {
		return [](float x, float y) {
			return engine.Joystick(AXIS_X);
		};
	}
};*/
/*
class InputDevce {
	virtual float read() = 0;
};

class KeyInputDevce : public InputDevce {
	virtual float read() {
		return engine.readKey(KEY_LEFT);
	};
};
class MouseInputDevce : public InputDevce {
	virtual float read() {
		return engine.readMouse(AXIS_X);
	};
};

class JoystickInputDevce : public InputDevce {
	virtual float read() {
		return engine.readJoystick(AXIS_X);
	};
};*/

// Normalize: v/length(v)
template<typename S, typename V>
V normalize(const V& v) {
	return mul(S(1) / length<S>(v), v);
}

int main() {
	auto func1 = makeMeAFunction(1);
	auto func2 = makeMeAFunction(15);
	printf("f1=%f\n", func1(1,2) );
	printf("f1=%f\n", func2(1, 2));
	printf("Start app!\n");
	printf("Start app!\n");
	typedef std::vector<float> Vec;
	
	using namespace mikroplot;
	Window window(800, 800, "Notebook 5 - Linear algebra");
#if 0
	auto v1 = Vec{ 1, 2 };
	auto v2 = Vec{ 3, 4 };
#else
	auto v2 = Vec{ 1, 2 };
	auto v1 = Vec{ 3, 4 };
#endif
	auto result = add(v1,v2);
	auto dotRes = dot<float>(v1,v1);
	auto v2Len = dot<float>(v2, v2);
	printf("v2Len=%f\n", v2Len);
	auto v3 = normalize<float>(v2);

	while (false == window.shouldClose()) {		
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();
#if 0
		window.drawLines({ {0,0}, v1}, 13, 2);
		//window.drawLines({ {0,0}, v2 }, 16, 2);
		window.drawPoints({ v1, v2 }, 13, 6);
		window.drawPoints({ result }, 12, 6);
		window.drawLines({ {0,0}, result }, 12, 2);
		// v2:n alkaen v1 paikasta
		window.drawLines({ v1, result }, 16, 2);
#endif

		window.drawLines({ {0,0}, v1 }, 11, 4);
		window.drawLines({ {0,0}, mul(2.0f, v1) }, 16, 2);

		window.update();
	}
	printf("End app!\n");
	return 0;
}
