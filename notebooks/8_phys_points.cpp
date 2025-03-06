#include <glm/glm.hpp>
#include <mikroplot/window.h>

struct Particle {
	glm::vec2 position; // 0. derivatta (paikka)
	glm::vec2 velocity;  // 1. derivatta (nopeus)
 };

void drawParticles(auto& window, const std::vector<Particle>& particles) {
	std::vector<mikroplot::vec2> mpPoints;
	for (auto p : particles)
	{
		mpPoints.push_back({ p.position.x , p.position.y });
	}
	auto color = 13;
	auto pointSize = 10;
	window.drawPoints(mpPoints, color, pointSize);
}



void drawPooints(auto& window, const std::vector<glm::vec2>& points) {
	std::vector<mikroplot::vec2> mpPoints;
	for (auto p: points) 
	{
		mpPoints.push_back({ p.x , p.y });
	}
	auto color = 13;
	auto pointSize = 10;
	window.drawPoints(mpPoints, color, pointSize);
}

auto integrateEuler(auto s, float dt, auto deriveFunc) {
	auto ds = deriveFunc(s, 0); // kysy derivaatta pisteessä N (=N+0)
	s = s + ds * dt;
	return s;
}

auto simulate(auto body, float dt) {
	// Nopeuden derivaatta on kiihtyvyys (tss pelkk gravitaatiovoima)
	auto dVel = [](auto s, float dt) {
		return glm::vec2(0, -0.81f);
	};


	// paika derivaatta on nopeus , joten palauta suoraan bodyn volocity.
	auto dPos = [&body](auto s, float dt) {
		return body.velocity;
	};

	body.velocity = integrateEuler(body.velocity, dt, dVel);
	body.position = integrateEuler(body.position, dt, dPos);
	return body;
}

std::vector<mikroplot::vec2> getEponetFunc(float dt){
	std::vector<mikroplot::vec2> realValues;
	float time = 0.0f;
	for (time = 0.0f; time <= 10.0f; time += dt)
	{
		realValues.push_back({ time, std::exp(time) });
	}
	return realValues;
}

std::vector<mikroplot::vec2> simulExpFunc(float dt) {
	std::vector<mikroplot::vec2> simulValues;
	simulValues.push_back({ 0, 1 }); // Eksponettifunktio: Ajamhetki 0 , paikka 1
	float time = 0.0f;
	auto deriveOfExp = [&time](auto s, float dt) {
		return std::exp(time); // exponettifuntion derivaatta hetkellä "time" on exponenttifunktio ajanhetkellä
	};

	for (time = dt; time <= 10.0f; time += dt) {
		auto prevValue = simulValues.back().y; // viimeisin y-arvo
		auto newValue = integrateEuler(prevValue, dt, deriveOfExp);
		simulValues.push_back({ time , newValue });
	}
	return simulValues;
}



int main() {
	mikroplot::Timer timer;
	mikroplot::Window window(900, 900, "Integrate points");

	std::vector<Particle> particles;
	particles.push_back(Particle{ {1, 2}, {1,0} });
	particles.push_back(Particle{ {2, 6}, {1,1} });

	// Laske oikeat exponenttifunktion arvot trace muuttajaan 
	std::vector<mikroplot::vec2> trace = getEponetFunc(0.1f);
	std::vector<mikroplot::vec2> traceSimul1 = simulExpFunc(0.1f);
	std::vector<mikroplot::vec2> traceSimul2 = simulExpFunc(0.5f);
	std::vector<mikroplot::vec2> traceSimul3 = simulExpFunc(1.0f);

	//std::vector<mikroplot::vec2> trace;
	//trace.push_back({ 0 , 0 });
	//trace.push_back({ 10, 10 });

	std::vector<glm::vec2> points;
	points.push_back({ 1, 2 });
	points.push_back({ 2, 6 });



	while (window.shouldClose()== false)
	{
		// TODO : Update objects
		float deltaTime = timer.getDeltaTime();
		for (auto& body : particles) {
			body = simulate(body, deltaTime);
		}


	   // Render:
		window.setScreen(-1, 11, -1, 11);
		window.drawAxis();
		// TODO: Piirrä muut objektit
		drawParticles(window, particles);
		window.drawLines( trace);
		window.drawLines(traceSimul1, 12);
		window.drawLines(traceSimul2, 14);
		window.drawLines(traceSimul3, 15);

		window.update();
	}
	return 0;
}