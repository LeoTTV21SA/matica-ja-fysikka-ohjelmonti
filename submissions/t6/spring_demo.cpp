//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <mikroplot/window.h>
//
//
//struct Particle {
//	glm::vec2 position;						// 0. derivaatta (paikka)
//	glm::vec2 velocity = glm::vec2(0.0f);	// 1. derivaatta (nopeus)
//};
//
//
//auto integrateEuler(auto x0, float dt, auto deriveFunc) {
//	auto dx = deriveFunc(x0, 0); // Kysy derivaatta pisteessä t+0
//	auto x1 = x0 + dx * dt;
//	return x1;
//}
//
//struct SpringSystem {
//	void update(float dt) {
//		// Nopeuden derivaatta on kiihtyvyys (tässä pelkkä gravitaatiovoima)
//		auto dVel = [this](auto s, float dt) {
//			auto x = particle.position - this->position;
//			return glm::vec2(0, -9.81f) - k * x;
//		};
//		// paikan derivaatta on nopeus, joten palauta suoraan bodyn velocity.
//		auto dPos = [this](auto s, float dt) {
//			return particle.velocity;
//		};
//		particle.velocity = integrateEuler(particle.velocity, dt, dVel);
//		particle.position = integrateEuler(particle.position, dt, dPos);
//		particle.velocity *= 0.99f;
//	}
//
//	glm::vec2 position;
//	Particle particle;
//	float k = 20.0f;
//};
//
//int main() {
//	mikroplot::Timer timer;
//	mikroplot::Window window(900, 900, "Spring demo");
//	SpringSystem spring;
//	spring.position.x = 5.0f;
//	spring.position.y = 10.0f;
//	spring.particle.position.x = spring.position.x;
//	spring.particle.position.y = spring.position.y - 2.0f;
//	spring.particle.velocity.x = 1.0f;
//	spring.particle.velocity.y = 0.0f;
//
//	float totalTime = 0.0f;
//	while (window.shouldClose() == false) {
//		// TODO: Update objects
//		float deltaTime = timer.getDeltaTime();
//		totalTime += deltaTime;
//
//		if (totalTime > 3.0f) {
//			spring.update(deltaTime);
//		}
//		// Render:
//		window.setScreen(-1, 11, -1, 11);
//		window.drawAxis();
//
//		std::vector< mikroplot::vec2> points;
//		points.push_back({ spring.position.x, spring.position.y });
//		points.push_back({ spring.particle.position.x, spring.particle.position.y });
//		window.drawPoints(points, 12, 10);
//
//
//
//		window.update();
//	}
//
//	return 0;
//}


















//#include <iostream>
//#include <glm/glm.hpp> // Incluir la biblioteca glm
//#include <mikroplot/window.h> // Incluir la biblioteca mikroplot
//
//const float k = 0.1f; // jousivakio
//const float m = 1.0f; // particle massa 
//const float g = 9.81f; // Painovoiman aiheuttama kiihtyvyys
//const float damping = 0.01f; // Vaimennusnopeus
//
////Window kokos 
//const int SCREEN_WIDTH = 900;
//const int SCREEN_HEIGHT = 900;
//
//
//int main() {
//	using namespace mikroplot;
//
//	// Crear la ventana de mikroplot
//	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Spring Demo");
//	float x =  5.0f;
//	float y =  10.0f;
//	float v = 0.0f;
//
//	while (window.shouldClose() == false)
//	{
//		window.setScreen(-5, 15, -1, 15);
//		window.drawAxis();
//
//		// lasket voimat
//		float spring_force = -k * y;
//		float gravitational_force = m * g;
//		float damping_force = -damping * v;
//
//		// plusta kaiki voimat
//		float total_force = spring_force + gravitational_force + damping_force;
//
//		// laske kihtyvys(calculate acceleration)
//		float a = total_force / m;
//
//		// update nopeus ja paikka 
//		v += a;
//		x += v;
//
//		std::vector<mikroplot::vec2>points = { {x, y} };
//		window.drawPoints(points, 12, 30);
//
//		window.update();
//	}
//	return 0;
//}


#include <iostream>
#include <glm/glm.hpp>
#include <mikroplot/window.h>

const float k = 0.1f; // jousivakio
const float m = 5.0f; // masa de la partícula
const float g = 9.81f; // aceleración debido a la gravedad
const float damping = 0.01f; // velocidad de amortiguamiento

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;

int main() {
    using namespace mikroplot;

    // Crear la ventana de mikroplot
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Spring Demo");

    // Posición inicial de la partícula en el suelo
    float x = SCREEN_WIDTH / 2.0f;
    float y = 0.0f;
    float v = 0.0f;

    while (!window.shouldClose()) {
        window.setScreen(x - SCREEN_WIDTH / 64.0f, x + SCREEN_WIDTH / 64.0f,
            y - SCREEN_HEIGHT / 64.0f, y + SCREEN_HEIGHT / 64.0f);
        window.drawAxis();

        // Calcular fuerzas
        float spring_force = -k * y; // La fuerza del resorte actúa en dirección positiva del eje Y
        float gravitational_force = m * g;
        float damping_force = -damping * v;

        // Calcular la fuerza total
        float total_force = spring_force + gravitational_force + damping_force;

        // Calcular la aceleración
        float a = total_force / m;

        // Actualizar la velocidad y la posición
        v += a;
        y += v;

        // Dibujar la partícula en su nueva posición
        std::vector<vec2> points = { {x, y} };
        window.drawPoints(points, 12, 10);

        window.update();
    }

    return 0;
}
