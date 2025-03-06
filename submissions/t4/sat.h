#pragma one 

#include <vector>
#include <limits>
#include <glm/glm.hpp>
#include <complex>



struct AABB {
	glm::vec2 position;
	glm::vec2 halfSize; // Puolikas koko
	float rotation = 0;
	bool collides = false;


	std::vector<glm::vec2> getVertices() const
	{
		std::vector<glm::vec2> res;
		res.push_back(glm::vec2(halfSize.x, halfSize.y));
		res.push_back(glm::vec2(halfSize.x, -halfSize.y));
		res.push_back(glm::vec2(-halfSize.x, -halfSize.y));
		res.push_back(glm::vec2(-halfSize.x, halfSize.y));


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

	/*std::vector<ContactManifold> contactPointsA = intersect(oa, ob);
	std::vector<ContactManifold> contactPointsB = intersect(ob, oa);
	if (contactPointsA.size() > 0 && contactPointsB.size() > 0) {
		contactPointsA.insert(contactPointsA.end(), contactPointsB.begin(), contactPointsB.end());
		return contactPointsA;
	}*/
}