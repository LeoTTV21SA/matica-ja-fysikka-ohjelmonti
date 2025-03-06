#include <stdio.h>
#include <string>
#include <vector>
#include <functional>
#include <assert.h>
#include <map>
#include <mikroplot/window.h>
#include "func_util.h"
#include <cmath>

typedef std::vector<float>  Vector;
typedef std::vector<Vector>  Matrix;

/*
Matrix m = {
	{1,2,3},
	{4,5,6},
	{7,8,9}
};
*/
// m[0] palauttaa ensimmäisen rivin 1,2,3
// m[1] palauttaa ensimmäisen rivin 4,5,6
// m[0][2] -> 3

namespace v {

	template<typename T>
	auto sub(const std::vector<T>& lhs, const std::vector<T>& rhs) {
		assert(lhs.size() == rhs.size());
		std::vector<T> res;
		for (size_t i = 0; i < lhs.size(); ++i) {
			res.push_back(lhs[i] - rhs[i]);
		}
		return res;
	}

	template<typename T>
	auto add(const std::vector<T>& lhs, const std::vector<T>& rhs) {
		std::vector<T> res;
		for (size_t i = 0; i < lhs.size(); ++i) {
			res.push_back(lhs[i] + rhs[i]);
		}
		return res;
	}

	// Skalaarilla kertominen
	template<typename T>
	auto mul(float s, const std::vector<T>& vec) {
		std::vector<T> res;
		for (size_t i = 0; i < vec.size(); ++i) {
			res.push_back(s * vec[i]);
		}
		return res;
	}

	// Pistetulo
	template<typename T>
	T dot(const std::vector<T>& lhs, const std::vector<T>& rhs) {
		assert(lhs.size() == rhs.size());
		T result = 0;
		for (size_t i = 0; i < lhs.size(); ++i) {
			result += lhs[i] * rhs[i];
		}
		return result;
	}

	// Vektorin pituus
	template<typename T>
	auto length(const std::vector<T>& vec) {
		return sqrt(dot(vec,vec));
	}

	// Vektorin normalisointi
	template<typename T>
	auto normalize(const std::vector<T>& vec) {
		return v::mul(1.0 / v::length(vec), vec);
	}

	// 3d/2d ristitulo


}



namespace m {
	template<typename T>
	auto zero(size_t n, size_t m) {
		std::vector< std::vector<T> > result;
		for (size_t i = 0; i < n; ++i) {
			result.push_back(std::vector<T>(m, T(0)));
		}
		return result;
	}

	template<typename T>
	auto identity(size_t n, size_t m) {
		auto result = zero<T>(n,m);
		for (size_t i = 0; i < n; ++i) {
			result[i][i] = 1; // Each diagonal value is 1
		}
		return result;
	}

	// Palauttaa "index" sarakkeen matriisista.
	template<typename T>
	auto col(const std::vector< std::vector<T> >& mat, size_t index) {
		std::vector<T> result;
		for (size_t i = 0; i < mat.size(); ++i) {
			result.push_back(mat[i][index]);
		}
		return result;
	}



	template<typename T>
	auto mul(
		const std::vector< std::vector<T> >& lhs,
		const std::vector< std::vector<T> >& rhs) {
		const auto N = lhs.size();
		const auto M = rhs.size();
		auto result = zero<T>(N, M);
		for (size_t i = 0; i < lhs.size(); ++i) {
			for (size_t j = 0; j < rhs[0].size(); ++j) {
				assert(i < result.size());
				assert(j < result[i].size());
				assert(i < lhs.size());
				assert(j < rhs[0].size());
				result[i][j] = v::dot(lhs[i], col(rhs, j));
			}
		}
		//result[0][0] = lhs[0][0]*rhs[0][0] + lhs[1][0] * rhs[0][0] + lhs[2][0] * rhs[0][0] +
		return result;
	}

	template<typename T>
	auto transpose(const std::vector< std::vector<T> >& mat) {
		const auto N = mat.size();
		const auto M = mat[0].size();
		auto result = m::zero<T>(M, N);
		for (size_t i = 0; i < M; ++i) {
			for (size_t j = 0; j < N; ++j) {
				assert(i < result.size());
				assert(j < result[i].size());
				assert(j < mat.size());
				assert(i < mat[j].size());
				result[i][j] = mat[j][i];
			}
		}
		return result;
	}


	template<typename T>
	auto mul(const std::vector< std::vector<T> >& mat,
		const std::vector<T>& vec) {
		auto rhsM = transpose(std::vector< std::vector<T> >({vec}));
		auto resultM = mul(mat, rhsM);
		resultM = transpose(resultM);
		return resultM[0];
	}
}


namespace tr {
	template<typename T>
	auto scaling(const std::vector<T>& scalingFactors) {
		/*
		Matrix identity = {
			{1,0,0},
			{0,1,0},
			{0,0,1}
		};
		Matrix sUniform = {
			{ks,0,0},
			{0,ks,0},
			{0,0,ks}
		};
		Matrix scale = {
			{kx,0,0},
			{0,ky,0},
			{0,0,kz}
		};
		*/
		auto N = scalingFactors.size() + 1;
		auto result = m::zero<T>(N, N);
		for (size_t i = 0; i < N; ++i) {
			if (i < scalingFactors.size()) {
				result[i][i] = scalingFactors[i];
			}
			else {
				result[i][i] = 1;
			}
		}
		return result;
	}

	template<typename T>
	auto translation(const std::vector<T>& translateValues) {
		/*Matrix translate = {
			{1,0,tx},
			{0,1,ty},
			{0,0,1}
		};*/
		auto N = translateValues.size() + 1;
		auto result = m::identity<T>(N, N);
		//auto lastCol = N - 1;
		for (size_t i = 0; i < translateValues.size(); ++i) {
			result[i][N - 1] = translateValues[i];
		}
		return result;
	}


	template<typename T>
	auto rotationZ(T angle) {
		return std::vector< std::vector<T> >({ 
			{cosf(angle), -sinf(angle), 0},
			{sinf(angle), cosf(angle), 0}, 
			{0, 0, 1} 
		});
	}

}

struct Transform {
	Transform* parent = 0;
	Vector position;
	float rotation = 0;

	Matrix getLocalTransform() const {
		auto rot = tr::rotationZ<float>(rotation);
		auto translation = tr::translation<float>(position);
		return m::mul(rot, translation);
	}

	Matrix getWorldTransform() const {
		if (parent == 0) {
			return getLocalTransform();
		}
		return m::mul(parent->getWorldTransform(), getLocalTransform());
	}
};


int main() {
	using namespace mikroplot;

	Window window(900, 900, "Vectors");
	int S = 3;

	/*Vector p1 = {-2, 3};
	Vector p2 = {3, 1.5};
	*/
	float angle = 0;
	while (!window.shouldClose()) {
		window.setScreen(-S, S, -S, S);
		window.drawAxis();
		angle += 3.1415 / 60.0f;

		//window.drawPoints({ vec2(p1[0],p1[1]) }, 9, 7);
		//window.drawPoints({ vec2(p2[0],p2[1]) }, 11, 7);

		/*auto v = v::sub(p2, p1);
		*/
		// Vektori 1,2 ja lisäksi homogeenisen koordinaatiston vaatima 1
		//Vector v = { 1, 2, 1 };

		/*window.drawLines({
			vec2(0,0),
			vec2(v[0],v[1]) 
		}, 11, 7);*/
			
		/*auto scaleMat = tr::scaling<float>(Vector({0.5,2}));
		auto translateMat = tr::translation<float>(Vector({ 3,1 }));
		auto rotatePiDiv2 = tr::rotationZ<float>(angle);
		v = m::mul<float>(rotatePiDiv2, v);
		window.drawLines({
			vec2(0,0),
			vec2(v[0],v[1])
		}, 16, 3);*/
#if 0
		Vector v = { 0, 0, 1 };
		window.drawLines({
			vec2(0,0),
			vec2(v[0],v[1])
		}, 11, 7);

		//auto scaleMat = tr::scaling<float>(Vector({ 0.5,2 }));
		auto translateMat = tr::translation<float>(Vector({ 1,0 }));
		auto rotatePiDiv4 = tr::rotationZ<float>(3.1415*0.25f);
		v = m::mul<float>(translateMat, v);
		v = m::mul<float>(rotatePiDiv4, v);
		window.drawLines({
			vec2(0,0),
			vec2(v[0],v[1])
			}, 11, 8);


		v = { 0, 0, 1 };
		v = m::mul<float>(m::mul(rotatePiDiv4,translateMat), v);
		window.drawLines({
			vec2(0,0),
			vec2(v[0],v[1])
			}, 17, 3);
#endif
		//float vLen = v::length(v);
		
/*

		Vector startPos = { 1, 2 };
		Vector endPoint = v::add(startPos, v);


		window.drawLines({
			vec2(startPos[0],startPos[1]),
			vec2(endPoint[0],endPoint[1])
		}, 16, 5);
		*/


		Transform o1;
		o1.position = Vector({ 1,0 });
		o1.rotation = 0.05*angle;
		o1.rotation = 0.0f;

		Transform o2;
		o2.position = Vector({ 1,0 });
		o2.rotation = -0.25f*angle;
		o2.parent = &o1;

		Transform o3;
		o3.position = Vector({ 1,0 });
		o3.parent = &o2;
		o3.rotation = 0.25f * angle;

		Vector v = { 0, 0, 1 };
		Vector v1 = m::mul<float>(o1.getWorldTransform(), v);
		Vector v2 = m::mul<float>(o2.getWorldTransform(), v);
		Vector v3 = m::mul<float>(o3.getWorldTransform(), v);
		window.drawLines({
			vec2(0,0),
			vec2(v1[0],v1[1]),
			vec2(v2[0],v2[1]),
			vec2(v3[0],v3[1])
			}, 11, 3);

		window.update();
	}

	return 0;
}














