#pragma once
#include <vector>

namespace func {

	auto gen(size_t N, auto /*std::function<int(size_t, int)>*/ f) {
		for (size_t n = 0; n < N; n++)
		{
			f(n);
		}
	};
	/// <summary>
	/// map([],f)->[] (otta parametrina vektorin ja funktion : f(size_t, int)->int
	/// palautta vektorin, joka jokaisella elementille on kutsuttu funktiota f.
	/// Funktiopointteri funktiotyypille f(void)->void, jomka nimi on func
	///  ja aseta se  null pointteriksi:
	/// </summary>
	template<typename V>
	auto map(const V& vec, auto /*std::function<int(size_t, int)>*/f ) {
		V result;
		// kaappaa muutuja "result" ,"f" ja "vec" lambdan sis‰‰n viittaiksena
		gen(vec.size(), [&result, &f, &vec](size_t i) {
			result.push_back(f(i, vec[i]));
			});
		return result;
	};

	template<typename T>
	auto filter(std::vector<T> v, auto f) {
		std::vector<T> result;
		gen(v.size(), [&](auto i) {
			if (f(i, v[i]) == true) {
				result.push_back(v[i]);
			}
			});
		return result;
	}
	/// <summary>
	/// fold/reduce function: fold(T[], f)-> T
	/// </summary>
	template<typename T>
	auto fold(std::vector<T> v, auto f, int initialValue = 0) {
		gen(v.size(), [&](auto i) {
			initialValue = f(initialValue, v[i]);
			});
		return initialValue;
	};
}