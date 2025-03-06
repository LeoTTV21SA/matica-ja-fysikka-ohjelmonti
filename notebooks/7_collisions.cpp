#include <mikroplot/window.h>
#include <array>
#include <cmath>

typedef std::array<float,2> Vector;

struct Sphere {
	Vector position;
	float radius;
	bool collides = false;
};

struct AABB {
	Vector position;
	Vector halfSize; // Puolikas koko
	// float rotation = 0;
	bool collides = false;
};


bool isSphereSphereCollision(const Sphere& o1, const Sphere& o2) {
	// d, eli paikkojen erotusvektorin pituus
	float dx = o2.position[0] - o1.position[0]; // erotus
	float dy = o2.position[1] - o1.position[1];
	float D = sqrtf(dx*dx + dy*dy); // pituus D
	return D <= (o1.radius+o2.radius);
}

bool isAABBCollision(const AABB& o1, const AABB& o2) {
	// d, eli paikkojen erotusvektorin pituus
	float dx = std::abs(o2.position[0] - o1.position[0]); // erotus
	float dy = std::abs(o2.position[1] - o1.position[1]);
	float sx = o1.halfSize[0] + o2.halfSize[0];
	float sy = o1.halfSize[1] + o2.halfSize[1];
	return dx <= sx && dy <= sy;
}

auto diffLength(const auto& v1, const auto& v2) {
	float dx = v1[0] - v2[0];
	float dy = v1[1] - v2[1];
	return sqrtf(dx*dx + dy*dy);
}

// Kyhn miehen box-sphere collision chekki....
bool isSphereBoxCollision(const Sphere& o1, const AABB& o2) {
	Vector p0 = { o2.position[0] - o2.halfSize[0], o2.position[1] - o2.halfSize[1] };
	Vector p1 = { o2.position[0] - o2.halfSize[0], o2.position[1] + o2.halfSize[1] };
	Vector p2 = { o2.position[0] + o2.halfSize[0], o2.position[1] + o2.halfSize[1] };
	Vector p3 = { o2.position[0] + o2.halfSize[0], o2.position[1] - o2.halfSize[1] };
	if (diffLength(p0, o1.position) <= o1.radius) return true;
	if (diffLength(p1, o1.position) <= o1.radius) return true;
	if (diffLength(p2, o1.position) <= o1.radius) return true;
	if (diffLength(p3, o1.position) <= o1.radius) return true;
	return false;
}


int main() {
	using namespace mikroplot;

	Window window(800, 800, "Collisions");

	std::vector<Sphere> spheres = {
		// pos,  radius
		{{0,0}, 0.5f},
		{{3,3}, 1.0f}
	};

	std::vector<AABB> aabbs = {
		// pos,  half size
		{{-2,1}, {0.5f,0.5f}},
		{{-3,3}, {1.0f,0.5f}}
	};

	auto checkAllCollisions = [&spheres,&aabbs]() {
		// oletetaan aluksi, ettei kukaan trm minnekkn
		for (size_t i = 0; i < spheres.size(); ++i) {
			spheres[i].collides = false;
		}
		for (size_t i = 0; i < aabbs.size(); ++i) {
			aabbs[i].collides = false;
		}
		// Sphere - sphere:
		for (size_t i = 0; i < spheres.size(); ++i) {
			for (size_t j = i+1; j < spheres.size(); ++j) {
				if (isSphereSphereCollision(spheres[i], spheres[j])) {
					spheres[i].collides = true;// Trmys, aseta lippu
					spheres[j].collides = true;// Trmys, aseta lippu
				}
			}
		}
		// Box - box:
		for (size_t i = 0; i < aabbs.size(); ++i) {
			for (size_t j = i + 1; j < aabbs.size(); ++j) {
				if (isAABBCollision(aabbs[i], aabbs[j])) {
					aabbs[i].collides = true;// Trmys, aseta lippu
					aabbs[j].collides = true;// Trmys, aseta lippu
				}
			}
		}

		for (size_t i = 0; i < aabbs.size(); ++i) {
			for (size_t j = 0; j < spheres.size(); ++j) {
				if (isSphereBoxCollision(spheres[j], aabbs[i])) {
					//aabbs[i].collides = spheres[j].collides = true;
					aabbs[i].collides = true;
					spheres[j].collides = true;
				}
			}
		}

	};

	float deltaTime = 1.0f / 60.0f;
	while (window.shouldClose() == false) {
		window.setScreen(-5, 5, -5, 5);
		window.drawAxis();
		float dx = window.getKeyState(KEY_RIGHT) - window.getKeyState(KEY_LEFT);
		float dy = window.getKeyState(KEY_UP)    - window.getKeyState(KEY_DOWN);
		//auto& playerSphere = spheres[0];
		auto& playerSphere = aabbs[0];
		// Eulerin integraatio:
		playerSphere.position[0] += dx * deltaTime;
		playerSphere.position[1] += dy * deltaTime;
		
		// TODO:
		checkAllCollisions();
		for (const auto& sphere : spheres) {
			int color = sphere.collides ? 14 : 11;
			window.drawCircle(
				{sphere.position[0],sphere.position[1]},
				sphere.radius, color);
		}

		for (const auto& box : aabbs) {
			int color = box.collides ? 14 : 11;
			std::vector<vec2> lines = {
				vec2{ box.position[0] + box.halfSize[0], box.position[1] + box.halfSize[1] },
				vec2{ box.position[0] + box.halfSize[0], box.position[1] - box.halfSize[1] },
				vec2{ box.position[0] - box.halfSize[0], box.position[1] - box.halfSize[1] },
				vec2{ box.position[0] - box.halfSize[0], box.position[1] + box.halfSize[1] },
				vec2{ box.position[0] + box.halfSize[0], box.position[1] + box.halfSize[1] },
			};
			window.drawLines(lines, color);
		}


		window.update();
	}

	return 0;
}
