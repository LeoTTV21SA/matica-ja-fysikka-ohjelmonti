#include <mikroplot/window.h>
#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <complex>
#include <assert.h>


struct AABB {
	glm::vec2 position;
	glm::vec2 halfSize; // Puolikas koko
	 float rotation = 0;
	bool collides = false;


	std::vector<glm::vec2> getVertices() const
	{
		std::vector<glm::vec2> res;
		res.push_back(glm::vec2( halfSize.x,  halfSize.y));
		res.push_back(glm::vec2( halfSize.x, -halfSize.y));
		res.push_back(glm::vec2(-halfSize.x, -halfSize.y));
		res.push_back(glm::vec2(-halfSize.x,  halfSize.y));
		
		
		auto orientation = std::complex<float>(std::cos(rotation), std::sin(rotation));
		for (auto& vert : res) 
		{
			auto p = std::complex<float>(vert.x, vert.y);
			auto x1 = orientation * p * orientation;               // pyöritä piste 
			vert = position + glm::vec2(x1.real(), x1.imag());     // Siirä  pistettä
		}
		return res;
	}

	
};
struct ContactManifold {
	glm::vec2 position;
	glm::vec2 normalA;
	glm::vec2 normalB;
	
};



auto isSATCollision(const auto& oa, const auto& ob) {
	auto intersect = [](const auto& oa, const auto& ob)
	{
		std::vector<ContactManifold> manifolds;
		const auto vertA = oa.getVertices();
		const auto vertB = ob.getVertices();

		float minPenetration = std::numeric_limits<float>::infinity();
		ContactManifold manif;

		for (size_t i = 0; i < vertA.size(); ++i) {
			const auto currentA = vertA[i];
			const auto nextA = vertA[(i + 1) % vertA.size()];
			const auto edgeA = nextA - currentA;
			// ristitulo : axis = glm ::cross ( glm::vec3(edgeA,0.0f), glm::vec3(0,0,-1)
			glm::vec2 axis = glm::vec2(-edgeA.y, edgeA.x); // Normalisoituna

			//Laske maksimit ja minimit kuinki laatiko verteksien projisiolle
			// tälle akselille:
			float aMaxProj, aMinProj, bMaxProj, bMinProj;
			aMaxProj = bMaxProj = -std::numeric_limits<float > ::infinity();
			aMinProj = bMinProj = std::numeric_limits<float > ::infinity();

			// laske projisiont objektin a kärkipistelle
			for (const auto pos : vertA)
			{
				const float proj = glm::dot(axis, pos);
				aMaxProj = std::max(aMaxProj, proj);
				aMinProj = std::min(aMinProj, proj);
			}
			// laske projisiont objektin a kärkipistelle
			for (const auto pos : vertB)
			{
				const float proj = glm::dot(axis, pos);
				bMaxProj = std::max(bMaxProj, proj);
				bMinProj = std::min(bMinProj, proj);
			}
			// Tarkista overläppääkö alueeet : jos ei overläppi, niin silloin 
			// erottava akseli on olemassa ja törmäystä ei tapahtu
			if (aMaxProj < bMinProj || aMinProj > bMaxProj)
			{
				manifolds.clear();
				return manifolds;
			}

			// overlap arvot: Aina positiivisia
			float overlap1 = aMaxProj - bMinProj;
			float overlap2 = bMaxProj - aMinProj;
			if (overlap1 < overlap2) {
				axis == -axis;
			}
			/// <Minimi overlap penetration Muutujaan >
			float penetration = std::min(overlap1, overlap2);
				if (penetration < minPenetration)
				{
					minPenetration = penetration;
					auto relativeCenter = ob.position - oa.position;
					float distance = glm::dot(relativeCenter, axis);
					manif.position = oa.position + axis * distance;
					manif.normalA = axis;
					manif.normalB = -axis;
				}
		
		}

		// jos funktion suoritus pääaee tänne asti , se tarkointaa, että erottavia 
		// akseleita ei ole olemassa, joten objektir törmäävät.
		manifolds.push_back(manif);
		return manifolds;
	};
	// preguntar esto 
	auto contA = intersect(oa, ob);
	auto contB = intersect(ob, oa);
	if (contA.size() > 0 && contB.size() > 0) {
		contA.insert(contA.end(), contB.begin(), contB.end());
		return contA;
	}
	return std::vector<ContactManifold>();
	
	           //std::vector<ContactManifold> contactPointsA = intersect(oa, ob);
               //	std::vector<ContactManifold> contactPointsB = intersect(ob, oa);
               //	if (contactPointsA.size() > 0 && contactPointsB.size() > 0) {
               //contactPointsA.insert(contactPointsA.end(), contactPointsB.begin(), contactPointsB.end());
               //		return contactPointsA;
               //	}
}




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
				for (const auto& manif:contactManifolds)
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
		playerSphere.position[0] += dx * deltaTime;
		playerSphere.position[1] += dy * deltaTime;
		playerSphere.rotation += dr * deltaTime; // rotation 

		// TODO:
		auto [contactsPoints , contactNormals] = checkAllCollisions();
		


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
