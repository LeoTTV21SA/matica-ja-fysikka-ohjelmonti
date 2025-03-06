#include <mikroplot/window.h>
#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <complex>
#include <assert.h>
#include "sat.h"






int main() {
	using namespace mikroplot;

	Window window(800, 800, "Separated Axis Theorem Collisions");


	std::vector<AABB> aabbs = {
		// pos,  half size
		{{-2,1}, {0.5f,0.5f} , 0.15f},
		{{-3,3}, {1.0f,0.5f}}
	};

	auto checkAllCollisions = [&aabbs]() {
		std::vector <mikroplot::vec2> contactPoints;
		std::vector <mikroplot::vec2> contactNormals;
		// oletetaan aluksi, ettei kukaan trm minnekkn
		for (size_t i = 0; i < aabbs.size(); ++i) {
			aabbs[i].collides = false;
		}
		// Box - box:
		for (size_t i = 0; i < aabbs.size(); ++i) {
			for (size_t j = i + 1; j < aabbs.size(); ++j) {
				auto contactManifolds = isSATCollision(aabbs[i], aabbs[j]);
				if (contactManifolds.size() > 0) {
					aabbs[i].collides = true;// Trmys, aseta lippu
					aabbs[j].collides = true;// Trmys, aseta lippu
				}
				glm::vec2 position(0.0f);
				glm::vec2 nA(0.0f);
				glm::vec2 nB(0.0f);
				for (const auto& manif : contactManifolds)
				{
					position += manif.position;
					nA += manif.normalA;
					nB += manif.normalB;
				}
				position /= float(contactManifolds.size());
				nA = glm::normalize(nA);
				nB = glm::normalize(nB);

				// Kontaktipisteet ja normaalit visualisointiin:
				contactPoints.push_back({ position.x, position.y });

				contactNormals.push_back({
					position.x,
					position.y });
				contactNormals.push_back({
					position.x + nA.x,
					position.y + nA.y });

				contactNormals.push_back({
					position.x,
					position.y });
				contactNormals.push_back({
					position.x + nB.x,
					position.y + nB.y });




			}
		}
		return std::make_tuple(contactPoints, contactNormals);
	};
	float speed = 0.005f;
	float deltaTime = 1.0f / 60.0f;
	while (window.shouldClose() == false) {
		window.setScreen(-5, 5, -5, 5);
		window.drawAxis();
		float dx = window.getKeyState(KEY_RIGHT) - window.getKeyState(KEY_LEFT);
		float dy = window.getKeyState(KEY_UP) - window.getKeyState(KEY_DOWN);
		float dr = window.getKeyState(KEY_A) - window.getKeyState(KEY_D);
		//auto& playerSphere = spheres[0];
		auto& playerSphere = aabbs[0];
		// Eulerin integraatio:
		playerSphere.position[0] += dx * deltaTime * speed;
		playerSphere.position[1] += dy * deltaTime * speed;
		playerSphere.rotation += dr * deltaTime * speed; // rotation 

		// TODO:
		auto [contactsPoints, contactNormals] = checkAllCollisions();


		for (const auto& box : aabbs) {
			// Kysy verteksit laatikolle:
			auto boxVertices = box.getVertices();

			// Muunna boxVertices mikroplotin vec2 vektoriksi "lines":
			std::vector<vec2> lines;
			for (const auto vert : boxVertices) {
				lines.push_back({ vert.x , vert.y });
			}
			// Sulje verteksi looppi lismll ensimminen piste kahteen kertaan:
			lines.push_back({ boxVertices[0].x, boxVertices[0].y });
			// Piirr viivat
			int color = box.collides ? 8 : 11;
			window.drawLines(lines, color);
		}
		window.drawPoints(contactsPoints, 16, 5);
		window.drawLines(contactNormals, 13, 1, false);


		window.update();
	}

	return 0;
}
