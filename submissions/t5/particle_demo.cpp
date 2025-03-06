#include <mikroplot/window.h>
#include<iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>

// Definiciones de constantes
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1500;
const int MAX_PARTICLES_PER_SECOND = 30;
const int PARTICLE_LIFETIME = 10000; // 10 segundos en milisegundos
const float GRAVITY = 9.8; // m/s^2

// Estructura para representar una part�cula
struct Particle {
	glm::vec2 position;
	glm::vec2 velocity;
	clock_t birthTime;
};

// Funci�n para generar una nueva part�cula
Particle createParticle() {
	Particle p;
	p.position = glm::vec2(0.0f, 1.0f);
	p.birthTime = clock();

	// Generar velocidad aleatoria dentro de un rango
	p.velocity.x = (float)(rand() % 200 - 100) / 100.0f;   // Velocidad en el eje X (-1 a 1)
	p.velocity.y = (float)(rand() % 200) / 100.0f + 8.0f;  // Velocidad en el eje Y (-2 a 0), negativa para ir hacia arriba
	std::cout << "Posicion: (" << p.position.x << ", " << p.position.y << ")" << std::endl;

	return p;
}

std::vector<Particle> particles;

int main() {
	using namespace mikroplot;

	// Crear la ventana de mikroplot
	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle Demo");

	// Semilla para la generaci�n de n�meros aleatorios
	srand(time(NULL));

	// Bucle principal
	while (window.shouldClose() == false)
	{
		window.setScreen(-5, 5, -5, 5);
		window.drawAxis();

		// Generar nuevas part�culas seg�n la tasa m�xima permitida
		clock_t currentTime = clock();
		double deltaTime = 500.0; // Inicializar deltaTime en caso de que no haya part�culas


		if (!particles.empty()) {

			// Si hay part�culas en el vector, calcular deltaTime utilizando la �ltima part�cula
			deltaTime = (currentTime - particles.back().birthTime) / (double)CLOCKS_PER_SEC;
		}

		int particlesToSpawn = deltaTime * MAX_PARTICLES_PER_SECOND;
		// Imprime la cantida de particulas que se genera en cada interacion 
		std::cout << "Particles to spawn: " << particlesToSpawn << std::endl;

		//genera nuevas particulas
		for (int i = 0; i < particlesToSpawn; ++i) {
			particles.push_back(createParticle());
		}
		std::cout << particlesToSpawn << std::endl;
		
		// Dibujar y actualizar todas las part�culas
		for (size_t i = 0; i < particles.size(); ++i) {
			Particle& p = particles[i];

			// Calcular la posici�n de la part�cula en funci�n del tiempo
			clock_t elapsedTime = currentTime - p.birthTime;

			float t = (float)elapsedTime / PARTICLE_LIFETIME;
			p.position += p.velocity * t;


			// Aplica la gravedad
			p.velocity.y -= GRAVITY * deltaTime;

			// Dibujar la part�cula como un punto en la posici�n actual
			std::vector<vec2> particlePoint = { { p.position.x, p.position.y } };
			window.drawPoints(particlePoint, 11, 15);

			// Eliminar las part�culas que hayan superado su tiempo de vida
			if (elapsedTime >= PARTICLE_LIFETIME * CLOCKS_PER_SEC) {
				particles.erase(particles.begin() + i);
				--i; // Ajustar el �ndice despu�s de borrar el elemento
			}

		}


		// Actualizar la ventana de mikroplot
		window.update();
	}

	return 0;
}
