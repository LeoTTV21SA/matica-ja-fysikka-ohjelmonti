#include <mikroplot/window.h>
#include <array>
#include <cmath>
#include <glm/glm.hpp>
#include <complex>
#include <vector>
#include <limits>
#include <tuple>

struct AABB {
    glm::vec2 position;
    glm::vec2 halfSize;
    float rotation = 0;
    bool collides = false;
    glm::vec2 velocity = { 0.0f, 0.0f };
    float speed = 0.0f;

    std::vector<glm::vec2> getVertices() const {
        std::vector<glm::vec2> res;
        res.push_back(glm::vec2(halfSize.x, halfSize.y));
        res.push_back(glm::vec2(halfSize.x, -halfSize.y));
        res.push_back(glm::vec2(-halfSize.x, -halfSize.y));
        res.push_back(glm::vec2(-halfSize.x, halfSize.y));
        
        
        auto orientation = std::complex<float>(std::cos(rotation), std::sin(rotation));
        for (auto& vert : res) {
            auto p = std::complex<float>(vert.x, vert.y);
            auto x1 = orientation * p * orientation;
            vert = position + glm::vec2(x1.real(), x1.imag());
        }
        return res;
    }
};

struct ContactManifold {
    glm::vec2 position;
    glm::vec2 normalA;
    glm::vec2 normalB;
    float penetration;
};

auto isSATCollision(const AABB& oa, const AABB& ob) {
    auto intersect = [](const AABB& oa, const AABB& ob) {
        std::vector<ContactManifold> manifolds;
        const auto vertA = oa.getVertices();
        const auto vertB = ob.getVertices();

        float minPenetration = std::numeric_limits<float>::infinity();
        ContactManifold manif;

        for (size_t i = 0; i < vertA.size(); ++i) {
            const auto currentA = vertA[i];
            const auto nextA = vertA[(i + 1) % vertA.size()];
            const auto edgeA = nextA - currentA;
            glm::vec2 axis = glm::vec2(-edgeA.y, edgeA.x);

            float aMaxProj, aMinProj, bMaxProj, bMinProj;
            aMaxProj = bMaxProj = -std::numeric_limits<float>::infinity();
            aMinProj = bMinProj = std::numeric_limits<float>::infinity();

            for (const auto pos : vertA) {
                const float proj = glm::dot(axis, pos);
                aMaxProj = std::max(aMaxProj, proj);
                aMinProj = std::min(aMinProj, proj);
            }

            for (const auto pos : vertB) {
                const float proj = glm::dot(axis, pos);
                bMaxProj = std::max(bMaxProj, proj);
                bMinProj = std::min(bMinProj, proj);
            }

            if (aMaxProj < bMinProj || aMinProj > bMaxProj) {
                manifolds.clear();
                return manifolds;
            }

            float overlap1 = aMaxProj - bMinProj;
            float overlap2 = bMaxProj - aMinProj;
            if (overlap1 < overlap2) {
                axis = -axis;
            }

            float penetration = std::min(overlap1, overlap2);
            if (penetration < minPenetration) {
                minPenetration = penetration;
                auto relativeCenter = ob.position - oa.position;
                float distance = glm::dot(relativeCenter, axis);
                manif.position = oa.position + axis * distance;
                manif.normalA = axis;
                manif.normalB = -axis;
                manif.penetration = penetration;
            }
        }

        manifolds.push_back(manif);
        return manifolds;
        };

    auto contA = intersect(oa, ob);
    auto contB = intersect(ob, oa);
    if (contA.size() > 0 && contB.size() > 0) {
        contA.insert(contA.end(), contB.begin(), contB.end());
        return contA;
    }
    return std::vector<ContactManifold>();
}

void resolveCollision(AABB& a, AABB& b, const glm::vec2& normal, float penetration) {
    // Coeficiente de restitución (1 para rebote perfecto)
    float restitution = 0.9f;

    // Calcular la velocidad relativa en la dirección de la normal
    glm::vec2 relativeVelocity = b.velocity - a.velocity;
    float velocityAlongNormal = glm::dot(relativeVelocity, normal);

    // No resolver si los objetos se están separando
    if (velocityAlongNormal == 0)
        return;

    // Calcular el impulso escalar
    float impulseScalar = -(1 + restitution) * velocityAlongNormal;
    float invMassA = 500.0f; // asumiendo masa de 1 para A
    float invMassB = 0.001f; // asumiendo masa de 1 para B

  
    // Aplicar el impulso a las velocidades
    glm::vec2 impulse = impulseScalar * normal;
    a.velocity += invMassA * impulse;
    b.velocity -= invMassB * impulse;


    // Corregir posiciones para evitar el solapamiento
    float percent = 0.2f; // porcentaje de corrección de posición
    glm::vec2 correction = (penetration / (invMassA + invMassB)) * percent * normal;
    a.position += invMassA * correction;
    b.position -= invMassB * correction;
}

int main() {
    using namespace mikroplot;

    Window window(800, 800, "Separated Axis Theorem Collisions");

    std::vector<AABB> aabbs = {
        {{0.0f, -4.0f}, {0.5f, 0.5f}, 0.0f, false, {0.0f, 0.0f}}, // Cuadrado pequeño controlado por el usuario
        {{-5.37f, 0.0f}, {0.5f, 5.59f}}, // Cuadrado grande inmóvil equina isquierda
        {{5.37, 0.0f},{0.5f , 5.59f} }, // cuadro grande inmovil
        {{0.0f, 2.0f},{1.5f , 1.5f} },  // cuadro grande inmovil
        {{0.0f, 5.8f},{4.8f ,0.25f}} // regtangulo superior inmovil 
    };

    auto checkAllCollisions = [&aabbs]() {
        std::vector<mikroplot::vec2> contactPoints;
        std::vector<mikroplot::vec2> contactNormals;

        for (size_t i = 0; i < aabbs.size(); ++i) {
            aabbs[i].collides = false;
        }

        for (size_t i = 0; i < aabbs.size(); ++i) {
            for (size_t j = i + 1; j < aabbs.size(); ++j) {
                auto contactManifolds = isSATCollision(aabbs[i], aabbs[j]);
                if (contactManifolds.size() > 0) {
                    aabbs[i].collides = true;
                    aabbs[j].collides = true;

                    glm::vec2 normal = contactManifolds[0].normalA;
                    float penetration = contactManifolds[0].penetration;

                    resolveCollision(aabbs[i], aabbs[j], normal, penetration);

                    for (const auto& manif : contactManifolds) {
                        contactPoints.push_back({ manif.position.x, manif.position.y });
                        contactNormals.push_back({ manif.position.x, manif.position.y });
                        contactNormals.push_back({ manif.position.x + manif.normalA.x, manif.position.y + manif.normalA.y });
                        contactNormals.push_back({ manif.position.x, manif.position.y });
                        contactNormals.push_back({ manif.position.x + manif.normalB.x, manif.position.y + manif.normalB.y });
                    }
                }
            }
        }
        return std::make_tuple(contactPoints, contactNormals);
        };

    float deltaTime = 1.0f / 60.0f;

    while (window.shouldClose() == false) {
        window.setScreen(-6, 6, -6, 6);
        window.drawAxis();

        float acceleration = 0.0f;
        if (window.getKeyState(KEY_UP)) acceleration = 1.0f;
        if (window.getKeyState(KEY_DOWN)) acceleration = -1.0f;
        float turn = 0.0f;
        if (window.getKeyState(KEY_LEFT)) turn = 1.0f;
        if (window.getKeyState(KEY_RIGHT)) turn = -1.0f;

        auto& playerCube = aabbs[0];

        playerCube.rotation += turn * deltaTime;
        playerCube.speed += acceleration * deltaTime;
        playerCube.speed *= 0.99f; // Fricción para reducir gradualmente la velocidad

        glm::vec2 direction = glm::vec2(std::cos(playerCube.rotation), std::sin(playerCube.rotation));
        playerCube.velocity = direction * playerCube.speed;
        playerCube.position += playerCube.velocity * deltaTime;


        auto [contactsPoints, contactNormals] = checkAllCollisions();

        for (const auto& box : aabbs) {
            auto boxVertices = box.getVertices();

            std::vector<vec2> lines;
            for (const auto vert : boxVertices) {
                lines.push_back({ vert.x , vert.y });
            }
            lines.push_back({ boxVertices[0].x, boxVertices[0].y });
            int color = box.collides ? 8 : 11;
            window.drawLines(lines, color);
        }
        window.drawPoints(contactsPoints, 16, 5);
        window.drawLines(contactNormals, 13, 1, false);

        window.update();
    }

    return 0;
}




/// codigo que funciona 

//#include <mikroplot/window.h>
//#include <array>
//#include <cmath>
//#include <glm/glm.hpp>
//#include <complex>
//#include <vector>
//#include <limits>
//#include <tuple>
//
//struct AABB {
//    glm::vec2 position;
//    glm::vec2 halfSize;
//    float rotation = 0;
//    bool collides = false;
//    glm::vec2 velocity = { 0.0f, 0.0f };
//
//    std::vector<glm::vec2> getVertices() const {
//        std::vector<glm::vec2> res;
//        res.push_back(glm::vec2(halfSize.x, halfSize.y));
//        res.push_back(glm::vec2(halfSize.x, -halfSize.y));
//        res.push_back(glm::vec2(-halfSize.x, -halfSize.y));
//        res.push_back(glm::vec2(-halfSize.x, halfSize.y));
//
//
//        auto orientation = std::complex<float>(std::cos(rotation), std::sin(rotation));
//        for (auto& vert : res) {
//            auto p = std::complex<float>(vert.x, vert.y);
//            auto x1 = orientation * p * orientation;
//            vert = position + glm::vec2(x1.real(), x1.imag());
//        }
//        return res;
//    }
//};
//
//struct ContactManifold {
//    glm::vec2 position;
//    glm::vec2 normalA;
//    glm::vec2 normalB;
//    float penetration;
//};
//
//auto isSATCollision(const AABB& oa, const AABB& ob) {
//    auto intersect = [](const AABB& oa, const AABB& ob) {
//        std::vector<ContactManifold> manifolds;
//        const auto vertA = oa.getVertices();
//        const auto vertB = ob.getVertices();
//
//        float minPenetration = std::numeric_limits<float>::infinity();
//        ContactManifold manif;
//
//        for (size_t i = 0; i < vertA.size(); ++i) {
//            const auto currentA = vertA[i];
//            const auto nextA = vertA[(i + 1) % vertA.size()];
//            const auto edgeA = nextA - currentA;
//            glm::vec2 axis = glm::vec2(-edgeA.y, edgeA.x);
//
//            float aMaxProj, aMinProj, bMaxProj, bMinProj;
//            aMaxProj = bMaxProj = -std::numeric_limits<float>::infinity();
//            aMinProj = bMinProj = std::numeric_limits<float>::infinity();
//
//            for (const auto pos : vertA) {
//                const float proj = glm::dot(axis, pos);
//                aMaxProj = std::max(aMaxProj, proj);
//                aMinProj = std::min(aMinProj, proj);
//            }
//
//            for (const auto pos : vertB) {
//                const float proj = glm::dot(axis, pos);
//                bMaxProj = std::max(bMaxProj, proj);
//                bMinProj = std::min(bMinProj, proj);
//            }
//
//            if (aMaxProj < bMinProj || aMinProj > bMaxProj) {
//                manifolds.clear();
//                return manifolds;
//            }
//
//            float overlap1 = aMaxProj - bMinProj;
//            float overlap2 = bMaxProj - aMinProj;
//            if (overlap1 < overlap2) {
//                axis = -axis;
//            }
//
//            float penetration = std::min(overlap1, overlap2);
//            if (penetration < minPenetration) {
//                minPenetration = penetration;
//                auto relativeCenter = ob.position - oa.position;
//                float distance = glm::dot(relativeCenter, axis);
//                manif.position = oa.position + axis * distance;
//                manif.normalA = axis;
//                manif.normalB = -axis;
//                manif.penetration = penetration;
//            }
//        }
//
//        manifolds.push_back(manif);
//        return manifolds;
//        };
//
//    auto contA = intersect(oa, ob);
//    auto contB = intersect(ob, oa);
//    if (contA.size() > 0 && contB.size() > 0) {
//        contA.insert(contA.end(), contB.begin(), contB.end());
//        return contA;
//    }
//    return std::vector<ContactManifold>();
//}
//
//void resolveCollision(AABB& a, AABB& b, const glm::vec2& normal, float penetration) {
//    // Coeficiente de restitución (1 para rebote perfecto)
//    float restitution = 0.9f;
//
//    // Calcular la velocidad relativa en la dirección de la normal
//    glm::vec2 relativeVelocity = b.velocity - a.velocity;
//    float velocityAlongNormal = glm::dot(relativeVelocity, normal);
//
//    // No resolver si los objetos se están separando
//    if (velocityAlongNormal == 0)
//        return;
//
//    // Calcular el impulso escalar
//    float impulseScalar = -(1 + restitution) * velocityAlongNormal;
//    float invMassA = 500.0f; // asumiendo masa de 1 para A
//    float invMassB = 0.001f; // asumiendo masa de 1 para B
//
//
//    // Aplicar el impulso a las velocidades
//    glm::vec2 impulse = impulseScalar * normal;
//    a.velocity += invMassA * impulse;
//    b.velocity -= invMassB * impulse;
//
//
//    // Corregir posiciones para evitar el solapamiento
//    float percent = 0.2f; // porcentaje de corrección de posición
//    glm::vec2 correction = (penetration / (invMassA + invMassB)) * percent * normal;
//    a.position += invMassA * correction;
//    b.position -= invMassB * correction;
//}
//
//int main() {
//    using namespace mikroplot;
//
//    Window window(800, 800, "Separated Axis Theorem Collisions");
//
//    std::vector<AABB> aabbs = {
//        {{0.0f, -4.0f}, {0.5f, 0.5f}, 0.0f, false, {0.0f, 0.0f}}, // Cuadrado pequeño controlado por el usuario
//        {{-5.37f, 0.0f}, {0.5f, 5.59f}}, // Cuadrado grande inmóvil equina isquierda
//        {{5.37, 0.0f},{0.5f , 5.59f} }, // cuadro grande inmovil
//        {{0.0f, 2.0f},{1.5f , 1.5f} },  // cuadro grande inmovil
//        {{0.0f, 5.8f},{4.8f ,0.25f}} // regtangulo superior inmovil 
//    };
//
//    auto checkAllCollisions = [&aabbs]() {
//        std::vector<mikroplot::vec2> contactPoints;
//        std::vector<mikroplot::vec2> contactNormals;
//
//        for (size_t i = 0; i < aabbs.size(); ++i) {
//            aabbs[i].collides = false;
//        }
//
//        for (size_t i = 0; i < aabbs.size(); ++i) {
//            for (size_t j = i + 1; j < aabbs.size(); ++j) {
//                auto contactManifolds = isSATCollision(aabbs[i], aabbs[j]);
//                if (contactManifolds.size() > 0) {
//                    aabbs[i].collides = true;
//                    aabbs[j].collides = true;
//
//                    glm::vec2 normal = contactManifolds[0].normalA;
//                    float penetration = contactManifolds[0].penetration;
//
//                    resolveCollision(aabbs[i], aabbs[j], normal, penetration);
//
//                    for (const auto& manif : contactManifolds) {
//                        contactPoints.push_back({ manif.position.x, manif.position.y });
//                        contactNormals.push_back({ manif.position.x, manif.position.y });
//                        contactNormals.push_back({ manif.position.x + manif.normalA.x, manif.position.y + manif.normalA.y });
//                        contactNormals.push_back({ manif.position.x, manif.position.y });
//                        contactNormals.push_back({ manif.position.x + manif.normalB.x, manif.position.y + manif.normalB.y });
//                    }
//                }
//            }
//        }
//        return std::make_tuple(contactPoints, contactNormals);
//        };
//
//    float deltaTime = 1.0f / 60.0f;
//
//    while (window.shouldClose() == false) {
//        window.setScreen(-6, 6, -6, 6);
//        window.drawAxis();
//
//        float dx = window.getKeyState(KEY_RIGHT) - window.getKeyState(KEY_LEFT);
//        float dy = window.getKeyState(KEY_UP) - window.getKeyState(KEY_DOWN);
//        float dr = window.getKeyState(KEY_A) - window.getKeyState(KEY_D);
//
//
//
//        auto& playerCube = aabbs[0];
//
//        playerCube.velocity = glm::vec2(dx, dy);
//        playerCube.rotation += dr * deltaTime;
//        playerCube.position += playerCube.velocity * deltaTime;
//
//
//        auto [contactsPoints, contactNormals] = checkAllCollisions();
//
//        for (const auto& box : aabbs) {
//            auto boxVertices = box.getVertices();
//
//            std::vector<vec2> lines;
//            for (const auto vert : boxVertices) {
//                lines.push_back({ vert.x , vert.y });
//            }
//            lines.push_back({ boxVertices[0].x, boxVertices[0].y });
//            int color = box.collides ? 8 : 11;
//            window.drawLines(lines, color);
//        }
//        window.drawPoints(contactsPoints, 16, 5);
//        window.drawLines(contactNormals, 13, 1, false);
//
//        window.update();
//    }
//
//    return 0;
//}







//#include <mikroplot/window.h>
//#include <array>
//#include <cmath>
//#include <glm/glm.hpp>
//#include <complex>
//#include <vector>
//#include <limits>
//#include <tuple>
//
//struct AABB {
//    glm::vec2 position;
//    glm::vec2 halfSize;
//    float rotation = 0;
//    bool collides = false;
//    glm::vec2 velocity = { 0.0f, 0.0f };
//
//    std::vector<glm::vec2> getVertices() const {
//        std::vector<glm::vec2> res;
//        res.push_back(glm::vec2(halfSize.x, halfSize.y));
//        res.push_back(glm::vec2(halfSize.x, -halfSize.y));
//        res.push_back(glm::vec2(-halfSize.x, -halfSize.y));
//        res.push_back(glm::vec2(-halfSize.x, halfSize.y));
//
//        auto orientation = std::complex<float>(std::cos(rotation), std::sin(rotation));
//        for (auto& vert : res) {
//            auto p = std::complex<float>(vert.x, vert.y);
//            auto x1 = orientation * p * orientation;
//            vert = position + glm::vec2(x1.real(), x1.imag());
//        }
//        return res;
//    }
//};
//
//struct ContactManifold {
//    glm::vec2 position;
//    glm::vec2 normalA;
//    glm::vec2 normalB;
//    float penetration;
//};
//
//auto isSATCollision(const AABB& oa, const AABB& ob) {
//    auto intersect = [](const AABB& oa, const AABB& ob) {
//        std::vector<ContactManifold> manifolds;
//        const auto vertA = oa.getVertices();
//        const auto vertB = ob.getVertices();
//
//        float minPenetration = std::numeric_limits<float>::infinity();
//        ContactManifold manif;
//
//        for (size_t i = 0; i < vertA.size(); ++i) {
//            const auto currentA = vertA[i];
//            const auto nextA = vertA[(i + 1) % vertA.size()];
//            const auto edgeA = nextA - currentA;
//            glm::vec2 axis = glm::vec2(-edgeA.y, edgeA.x);
//
//            float aMaxProj, aMinProj, bMaxProj, bMinProj;
//            aMaxProj = bMaxProj = -std::numeric_limits<float>::infinity();
//            aMinProj = bMinProj = std::numeric_limits<float>::infinity();
//
//            for (const auto pos : vertA) {
//                const float proj = glm::dot(axis, pos);
//                aMaxProj = std::max(aMaxProj, proj);
//                aMinProj = std::min(aMinProj, proj);
//            }
//
//            for (const auto pos : vertB) {
//                const float proj = glm::dot(axis, pos);
//                bMaxProj = std::max(bMaxProj, proj);
//                bMinProj = std::min(bMinProj, proj);
//            }
//
//            if (aMaxProj < bMinProj || aMinProj > bMaxProj) {
//                manifolds.clear();
//                return manifolds;
//            }
//
//            float overlap1 = aMaxProj - bMinProj;
//            float overlap2 = bMaxProj - aMinProj;
//            if (overlap1 < overlap2) {
//                axis = -axis;
//            }
//
//            float penetration = std::min(overlap1, overlap2);
//            if (penetration < minPenetration) {
//                minPenetration = penetration;
//                auto relativeCenter = ob.position - oa.position;
//                float distance = glm::dot(relativeCenter, axis);
//                manif.position = oa.position + axis * distance;
//                manif.normalA = axis;
//                manif.normalB = -axis;
//                manif.penetration = penetration;
//            }
//        }
//
//        manifolds.push_back(manif);
//        return manifolds;
//    };
//
//    auto contA = intersect(oa, ob);
//    auto contB = intersect(ob, oa);
//    if (contA.size() > 0 && contB.size() > 0) {
//        contA.insert(contA.end(), contB.begin(), contB.end());
//        return contA;
//    }
//    return std::vector<ContactManifold>();
//}
//
//void resolveCollision(AABB& a, AABB& b, const glm::vec2& normal, float penetration) {
//    // Coeficiente de restitución (1 para rebote perfecto)
//    float restitution = 1.0f;
//
//    // Calcular la velocidad relativa en la dirección de la normal
//    glm::vec2 relativeVelocity = b.velocity - a.velocity;
//    float velocityAlongNormal = glm::dot(relativeVelocity, normal);
//
//    // No resolver si los objetos se están separando
//    if (velocityAlongNormal == 0)
//        return;
//
//    // Calcular el impulso escalar
//    float impulseScalar =  restitution * velocityAlongNormal;
//
//    // Aplicar el impulso a las velocidades
//    glm::vec2 impulse = impulseScalar * normal;
//    a.velocity += impulse;
//    b.velocity -= impulse;
//
//    // Corregir posiciones para evitar el solapamiento
//    float percent = 0.2f; // porcentaje de corrección de posición
//    glm::vec2 correction = (penetration / (a.halfSize.x + b.halfSize.x)) * percent * normal;
//    a.position += correction;
//    b.position -= correction;
//}
//
//int main() {
//    using namespace mikroplot;
//
//    Window window(800, 800, "Separated Axis Theorem Collisions");
//
//    std::vector<AABB> aabbs = {
//        {{-2, 1}, {0.5f, 0.5f}, 0.15f, false, {0.0f, 0.0f}}, // Cuadrado pequeño controlado por el usuario
//        {{-3, 3}, {1.0f, 0.5f}} // Cuadrado grande inmóvil
//    };
//
//    auto checkAllCollisions = [&aabbs]() {
//        std::vector<mikroplot::vec2> contactPoints;
//        std::vector<mikroplot::vec2> contactNormals;
//
//        for (size_t i = 0; i < aabbs.size(); ++i) {
//            aabbs[i].collides = false;
//        }
//
//        for (size_t i = 0; i < aabbs.size(); ++i) {
//            for (size_t j = i + 1; j < aabbs.size(); ++j) {
//                auto contactManifolds = isSATCollision(aabbs[i], aabbs[j]);
//                if (contactManifolds.size() > 0) {
//                    aabbs[i].collides = true;
//                    aabbs[j].collides = true;
//
//                    glm::vec2 normal = contactManifolds[0].normalA;
//                    float penetration = contactManifolds[0].penetration;
//
//                    resolveCollision(aabbs[i], aabbs[j], normal, penetration);
//
//                    for (const auto& manif : contactManifolds) {
//                        contactPoints.push_back({ manif.position.x, manif.position.y });
//                        contactNormals.push_back({ manif.position.x, manif.position.y });
//                        contactNormals.push_back({ manif.position.x + manif.normalA.x, manif.position.y + manif.normalA.y });
//                        contactNormals.push_back({ manif.position.x, manif.position.y });
//                        contactNormals.push_back({ manif.position.x + manif.normalB.x, manif.position.y + manif.normalB.y });
//                    }
//                }
//            }
//        }
//        return std::make_tuple(contactPoints, contactNormals);
//    };
//
//    float deltaTime = 1.0f / 60.0f;
//    while (window.shouldClose() == false) {
//        window.setScreen(-5, 5, -5, 5);
//        window.drawAxis();
//
//        float dx = window.getKeyState(KEY_RIGHT) - window.getKeyState(KEY_LEFT);
//        float dy = window.getKeyState(KEY_UP) - window.getKeyState(KEY_DOWN);
//        float dr = window.getKeyState(KEY_A) - window.getKeyState(KEY_D);
//
//        auto& playerCube = aabbs[0];
//        playerCube.velocity = glm::vec2(dx, dy);
//        playerCube.rotation += dr * deltaTime;
//        playerCube.position += playerCube.velocity * deltaTime;
//
//        auto [contactsPoints, contactNormals] = checkAllCollisions();
//
//        for (const auto& box : aabbs) {
//            auto boxVertices = box.getVertices();
//
//            std::vector<vec2> lines;
//            for (const auto vert : boxVertices) {
//                lines.push_back({ vert.x , vert.y });
//            }
//            lines.push_back({ boxVertices[0].x, boxVertices[0].y });
//            int color = box.collides ? 8 : 11;
//            window.drawLines(lines, color);
//        }
//        window.drawPoints(contactsPoints, 16, 5);
//        window.drawLines(contactNormals, 13, 1, false);
//
//        window.update();
//    }
//
//    return 0;
//}




//#include <mikroplot/window.h>
//#include <array>
//#include <cmath>
//#include <glm/glm.hpp>
//#include <complex>
//#include <vector>
//#include <limits>
//#include <tuple>
//
//struct AABB {
//    glm::vec2 position;
//    glm::vec2 halfSize;
//    float rotation = 0;
//    bool collides = false;
//    glm::vec2 velocity = { 0.0f, 0.0f };
//
//    std::vector<glm::vec2> getVertices() const {
//        std::vector<glm::vec2> res;
//        res.push_back(glm::vec2(halfSize.x, halfSize.y));
//        res.push_back(glm::vec2(halfSize.x, -halfSize.y));
//        res.push_back(glm::vec2(-halfSize.x, -halfSize.y));
//        res.push_back(glm::vec2(-halfSize.x, halfSize.y));
//
//        auto orientation = std::complex<float>(std::cos(rotation), std::sin(rotation));
//        for (auto& vert : res) {
//            auto p = std::complex<float>(vert.x, vert.y);
//            auto x1 = orientation * p * orientation;
//            vert = position + glm::vec2(x1.real(), x1.imag());
//        }
//        return res;
//    }
//};
//
//struct ContactManifold {
//    glm::vec2 position;
//    glm::vec2 normalA;
//    glm::vec2 normalB;
//};
//
//auto isSATCollision(const AABB& oa, const AABB& ob) {
//    auto intersect = [](const AABB& oa, const AABB& ob) {
//        std::vector<ContactManifold> manifolds;
//        const auto vertA = oa.getVertices();
//        const auto vertB = ob.getVertices();
//
//        float minPenetration = std::numeric_limits<float>::infinity();
//        ContactManifold manif;
//
//        for (size_t i = 0; i < vertA.size(); ++i) {
//            const auto currentA = vertA[i];
//            const auto nextA = vertA[(i + 1) % vertA.size()];
//            const auto edgeA = nextA - currentA;
//            glm::vec2 axis = glm::vec2(-edgeA.y, edgeA.x);
//
//            float aMaxProj, aMinProj, bMaxProj, bMinProj;
//            aMaxProj = bMaxProj = -std::numeric_limits<float>::infinity();
//            aMinProj = bMinProj = std::numeric_limits<float>::infinity();
//
//            for (const auto pos : vertA) {
//                const float proj = glm::dot(axis, pos);
//                aMaxProj = std::max(aMaxProj, proj);
//                aMinProj = std::min(aMinProj, proj);
//            }
//
//            for (const auto pos : vertB) {
//                const float proj = glm::dot(axis, pos);
//                bMaxProj = std::max(bMaxProj, proj);
//                bMinProj = std::min(bMinProj, proj);
//            }
//
//            if (aMaxProj < bMinProj || aMinProj > bMaxProj) {
//                manifolds.clear();
//                return manifolds;
//            }
//
//            float overlap1 = aMaxProj - bMinProj;
//            float overlap2 = bMaxProj - aMinProj;
//            if (overlap1 < overlap2) {
//                axis = -axis;
//            }
//
//            float penetration = std::min(overlap1, overlap2);
//            if (penetration < minPenetration) {
//                minPenetration = penetration;
//                auto relativeCenter = ob.position - oa.position;
//                float distance = glm::dot(relativeCenter, axis);
//                manif.position = oa.position + axis * distance;
//                manif.normalA = axis;
//                manif.normalB = -axis;
//            }
//        }
//
//        manifolds.push_back(manif);
//        return manifolds;
//    };
//
//    auto contA = intersect(oa, ob);
//    auto contB = intersect(ob, oa);
//    if (contA.size() > 0 && contB.size() > 0) {
//        contA.insert(contA.end(), contB.begin(), contB.end());
//        return contA;
//    }
//    return std::vector<ContactManifold>();
//}
//
//int main() {
//    using namespace mikroplot;
//
//    Window window(800, 800, "Separated Axis Theorem Collisions");
//
//    std::vector<AABB> aabbs = {
//        {{-2, 1}, {0.5f, 0.5f}, 0.15f, false, {5.0f, 0.0f}}, // Esfera con velocidad inicial
//        {{-3, 3}, {1.0f, 0.5f}}
//    };
//
//    auto checkAllCollisions = [&aabbs]() {
//        std::vector<mikroplot::vec2> contactPoints;
//        std::vector<mikroplot::vec2> contactNormals;
//
//        for (size_t i = 0; i < aabbs.size(); ++i) {
//            aabbs[i].collides = false;
//        }
//
//        for (size_t i = 0; i < aabbs.size(); ++i) {
//            for (size_t j = i + 1; j < aabbs.size(); ++j) {
//                auto contactManifolds = isSATCollision(aabbs[i], aabbs[j]);
//                if (contactManifolds.size() > 0) {
//                    aabbs[i].collides = true;
//                    aabbs[j].collides = true;
//
//                    glm::vec2 normal = contactManifolds[0].normalA;
//                    glm::vec2 relativeVelocity = aabbs[i].velocity - aabbs[j].velocity;
//                    float velocityAlongNormal = glm::dot(relativeVelocity, normal);
//
//                    if (velocityAlongNormal == 0) {
//                        float restitution = 1.0f; // Coeficiente de restitución (1 para rebote perfecto)
//                        glm::vec2 impulse = -(1 + restitution) * velocityAlongNormal * normal;
//                        aabbs[i].velocity += impulse;
//                    }
//
//                    // Reposicionar para evitar solapamiento
//                    aabbs[i].position += normal * 0.01f;
//                }
//
//                glm::vec2 position(0.0f);
//                glm::vec2 nA(0.0f);
//                glm::vec2 nB(0.0f);
//                for (const auto& manif : contactManifolds) {
//                    position += manif.position;
//                    nA += manif.normalA;
//                    nB += manif.normalB;
//                }
//                position /= float(contactManifolds.size());
//                nA = glm::normalize(nA);
//                nB = glm::normalize(nB);
//
//                contactPoints.push_back({ position.x, position.y });
//                contactNormals.push_back({ position.x, position.y });
//                contactNormals.push_back({ position.x + nA.x, position.y + nA.y });
//                contactNormals.push_back({ position.x, position.y });
//                contactNormals.push_back({ position.x + nB.x, position.y + nB.y });
//            }
//        }
//        return std::make_tuple(contactPoints, contactNormals);
//    };
//
//    float deltaTime = 1.0f / 60.0f;
//    while (window.shouldClose() == false) {
//        window.setScreen(-5, 5, -5, 5);
//        window.drawAxis();
//
//        float dx = window.getKeyState(KEY_RIGHT) - window.getKeyState(KEY_LEFT);
//        float dy = window.getKeyState(KEY_UP) - window.getKeyState(KEY_DOWN);
//        float dr = window.getKeyState(KEY_A) - window.getKeyState(KEY_D);
//
//        auto& playerSphere = aabbs[0];
//        playerSphere.velocity += glm::vec2(dx, dy) * deltaTime;
//        playerSphere.rotation += dr * deltaTime;
//        playerSphere.position += playerSphere.velocity * deltaTime;
//
//        auto [contactsPoints, contactNormals] = checkAllCollisions();
//
//        for (const auto& box : aabbs) {
//            auto boxVertices = box.getVertices();
//
//            std::vector<vec2> lines;
//            for (const auto vert : boxVertices) {
//                lines.push_back({ vert.x , vert.y });
//            }
//            lines.push_back({ boxVertices[0].x, boxVertices[0].y });
//            int color = box.collides ? 8 : 11;
//            window.drawLines(lines, color);
//        }
//        window.drawPoints(contactsPoints, 16, 5);
//        window.drawLines(contactNormals, 13, 1, false);
//
//        window.update();
//    }
//
//    return 0;
//}























//#include <mikroplot/window.h>
//#include <array>
//#include <cmath>
//#include <glm/glm.hpp>
//#include <complex>
//#include <assert.h>
//
//
//struct AABB {
//	glm::vec2 position;
//	glm::vec2 halfSize; // Puolikas koko
//	float rotation = 0;
//	bool collides = false;
//
//
//	std::vector<glm::vec2> getVertices() const
//	{
//		std::vector<glm::vec2> res;
//		res.push_back(glm::vec2(halfSize.x, halfSize.y));
//		res.push_back(glm::vec2(halfSize.x, -halfSize.y));
//		res.push_back(glm::vec2(-halfSize.x, -halfSize.y));
//		res.push_back(glm::vec2(-halfSize.x, halfSize.y));
//
//
//		auto orientation = std::complex<float>(std::cos(rotation), std::sin(rotation));
//		for (auto& vert : res)
//		{
//			auto p = std::complex<float>(vert.x, vert.y);
//			auto x1 = orientation * p * orientation;               // pyöritä piste 
//			vert = position + glm::vec2(x1.real(), x1.imag());     // Siirä  pistettä
//		}
//		return res;
//	}
//
//
//};
//struct ContactManifold {
//	glm::vec2 position;
//	glm::vec2 normalA;
//	glm::vec2 normalB;
//
//};
//
//
//
//auto isSATCollision(const auto& oa, const auto& ob) {
//	auto intersect = [](const auto& oa, const auto& ob)
//	{
//		std::vector<ContactManifold> manifolds;
//		const auto vertA = oa.getVertices();
//		const auto vertB = ob.getVertices();
//
//		float minPenetration = std::numeric_limits<float>::infinity();
//		ContactManifold manif;
//
//		for (size_t i = 0; i < vertA.size(); ++i) {
//			const auto currentA = vertA[i];
//			const auto nextA = vertA[(i + 1) % vertA.size()];
//			const auto edgeA = nextA - currentA;
//			// ristitulo : axis = glm ::cross ( glm::vec3(edgeA,0.0f), glm::vec3(0,0,-1)
//			glm::vec2 axis = glm::vec2(-edgeA.y, edgeA.x); // Normalisoituna
//
//			//Laske maksimit ja minimit kuinki laatiko verteksien projisiolle
//			// tälle akselille:
//			float aMaxProj, aMinProj, bMaxProj, bMinProj;
//			aMaxProj = bMaxProj = -std::numeric_limits<float > ::infinity();
//			aMinProj = bMinProj = std::numeric_limits<float > ::infinity();
//
//			// laske projisiont objektin a kärkipistelle
//			for (const auto pos : vertA)
//			{
//				const float proj = glm::dot(axis, pos);
//				aMaxProj = std::max(aMaxProj, proj);
//				aMinProj = std::min(aMinProj, proj);
//			}
//			// laske projisiont objektin a kärkipistelle
//			for (const auto pos : vertB)
//			{
//				const float proj = glm::dot(axis, pos);
//				bMaxProj = std::max(bMaxProj, proj);
//				bMinProj = std::min(bMinProj, proj);
//			}
//			// Tarkista overläppääkö alueeet : jos ei overläppi, niin silloin 
//			// erottava akseli on olemassa ja törmäystä ei tapahtu
//			if (aMaxProj < bMinProj || aMinProj > bMaxProj)
//			{
//				manifolds.clear();
//				return manifolds;
//			}
//
//			// overlap arvot: Aina positiivisia
//			float overlap1 = aMaxProj - bMinProj;
//			float overlap2 = bMaxProj - aMinProj;
//			if (overlap1 < overlap2) {
//				axis == -axis;
//			}
//			/// <Minimi overlap penetration Muutujaan >
//			float penetration = std::min(overlap1, overlap2);
//			if (penetration < minPenetration)
//			{
//				minPenetration = penetration;
//				auto relativeCenter = ob.position - oa.position;
//				float distance = glm::dot(relativeCenter, axis);
//				manif.position = oa.position + axis * distance;
//				manif.normalA = axis;
//				manif.normalB = -axis;
//			}
//
//		}
//
//		// jos funktion suoritus pääaee tänne asti , se tarkointaa, että erottavia 
//		// akseleita ei ole olemassa, joten objektir törmäävät.
//		manifolds.push_back(manif);
//		return manifolds;
//	};
//	// preguntar esto 
//	auto contA = intersect(oa, ob);
//	auto contB = intersect(ob, oa);
//	if (contA.size() > 0 && contB.size() > 0) {
//		contA.insert(contA.end(), contB.begin(), contB.end());
//		return contA;
//	}
//	return std::vector<ContactManifold>();
//
//	//std::vector<ContactManifold> contactPointsA = intersect(oa, ob);
//	//	std::vector<ContactManifold> contactPointsB = intersect(ob, oa);
//	//	if (contactPointsA.size() > 0 && contactPointsB.size() > 0) {
//	//contactPointsA.insert(contactPointsA.end(), contactPointsB.begin(), contactPointsB.end());
//	//		return contactPointsA;
//	//	}
//}
//
//
//
//
//int main() {
//	using namespace mikroplot;
//
//	Window window(800, 800, "Separated Axis Theorem Collisions");
//
//
//	std::vector<AABB> aabbs = {
//		// pos,  half size
//		{{-2,1}, {0.5f,0.5f} , 0.15f},
//		{{-3,3}, {1.0f,0.5f}}
//	};
//
//	auto checkAllCollisions = [&aabbs]() {
//		std::vector <mikroplot::vec2> contactPoints;
//		std::vector <mikroplot::vec2> contactNormals;
//		// oletetaan aluksi, ettei kukaan trm minnekkn
//		for (size_t i = 0; i < aabbs.size(); ++i) {
//			aabbs[i].collides = false;
//		}
//		// Box - box:
//		for (size_t i = 0; i < aabbs.size(); ++i) {
//			for (size_t j = i + 1; j < aabbs.size(); ++j) {
//				auto contactManifolds = isSATCollision(aabbs[i], aabbs[j]);
//				if (contactManifolds.size() > 0) {
//					aabbs[i].collides = true;// Trmys, aseta lippu
//					aabbs[j].collides = true;// Trmys, aseta lippu
//				}
//				glm::vec2 position(0.0f);
//				glm::vec2 nA(0.0f);
//				glm::vec2 nB(0.0f);
//				for (const auto& manif : contactManifolds)
//				{
//					position += manif.position;
//					nA += manif.normalA;
//					nB += manif.normalB;
//				}
//				position /= float(contactManifolds.size());
//				nA = glm::normalize(nA);
//				nB = glm::normalize(nB);
//
//				// Kontaktipisteet ja normaalit visualisointiin:
//				contactPoints.push_back({ position.x, position.y });
//
//				contactNormals.push_back({
//					position.x,
//					position.y });
//				contactNormals.push_back({
//					position.x + nA.x,
//					position.y + nA.y });
//
//				contactNormals.push_back({
//					position.x,
//					position.y });
//				contactNormals.push_back({
//					position.x + nB.x,
//					position.y + nB.y });
//
//
//
//
//			}
//		}
//		return std::make_tuple(contactPoints, contactNormals);
//	};
//
//	float deltaTime = 1.0f / 60.0f;
//	while (window.shouldClose() == false) {
//		window.setScreen(-5, 5, -5, 5);
//		window.drawAxis();
//		float dx = window.getKeyState(KEY_RIGHT) - window.getKeyState(KEY_LEFT) ;
//		float dy = window.getKeyState(KEY_UP) - window.getKeyState(KEY_DOWN);
//		float dr = window.getKeyState(KEY_A) - window.getKeyState(KEY_D);
//		//auto& playerSphere = spheres[0];
//		auto& playerSphere = aabbs[0];
//		// Eulerin integraatio:
//		playerSphere.position[0] += dx * deltaTime ;
//		playerSphere.position[1] += dy * deltaTime ;
//		playerSphere.rotation += dr * deltaTime; // rotation 
//
//		// TODO:
//		auto [contactsPoints, contactNormals] = checkAllCollisions();
//
//
//
//		for (const auto& box : aabbs) {
//			// Kysy verteksit laatikolle:
//			auto boxVertices = box.getVertices();
//
//			// Muunna boxVertices mikroplotin vec2 vektoriksi "lines":
//			std::vector<vec2> lines;
//			for (const auto vert : boxVertices) {
//				lines.push_back({ vert.x , vert.y });
//			}
//			// Sulje verteksi looppi lismll ensimminen piste kahteen kertaan:
//			lines.push_back({ boxVertices[0].x, boxVertices[0].y });
//			// Piirr viivat
//			int color = box.collides ? 8 : 11;
//			window.drawLines(lines, color);
//		}
//		window.drawPoints(contactsPoints, 16, 5);
//		window.drawLines(contactNormals, 13, 1, false);
//
//
//
//		window.update();
//	}
//
//	return 0;
//}
