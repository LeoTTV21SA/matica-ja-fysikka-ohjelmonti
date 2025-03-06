#include "math.h"
#include <stdexcept>
#include <iostream>
#include <cmath>


// En math.cpp, implementa la función de comparación personalizada
bool math::areEqual(const math::vec2& a, const math::vec2& b, float epsilon) {
    for (int i = 0; i < 2; ++i) {
        if (std::abs(a[i] - b[i]) > epsilon) {
            return false;
        }
    }
    return true;
}

bool math::areEqual(const math::vec3& a, const math::vec3& b, float epsilon) {
    for (int i = 0; i < 3; ++i) {
        if (std::abs(a[i] - b[i]) > epsilon) {
            return false;
        }
    }
    return true;
}



// Lysin tmn koodin verkosta ja sen pitisi ratkaista "Pipeline" - virhe
namespace math {

    std::string to_string(const math::vec2& vector) {
        return "[" + std::to_string(vector[0]) + ", " + std::to_string(vector[1]) + "]";
    }

     std::string to_string(const math::vec3& vector) {
        return "[" + std::to_string(vector[0]) + ", " + std::to_string(vector[1]) + "," + std::to_string(vector[2]) + "]";
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    /// 

    vec2 add(const vec2& lhs, const vec2& rhs) {
        return { lhs[0] + rhs[0], lhs[1] + rhs[1] };
    }

    vec2 sub(const vec2& lhs, const vec2& rhs) {
        return { lhs[0] - rhs[0], lhs[1] - rhs[1] };
    }

    vec2 mul(float scalar, const vec2& vector) {
        return { scalar * vector[0], scalar * vector[1] };
    }

    vec2 mul(const vec2& lhs, float rhs) {
        return { lhs[0] * rhs, lhs[1] * rhs };
    }

    vec2 div(const vec2& lhs, float rhs) {
        if (rhs != 0.0f) {
            return { lhs[0] / rhs, lhs[1] / rhs };
        }
        else {
            throw std::runtime_error("Error: divisin por cero.");
        }
    }

    float dot(const vec2& lhs, const vec2& rhs) {
        return lhs[0] * rhs[0] + lhs[1] * rhs[1];
    }

    float cross(const vec2& lhs, const vec2& rhs) {
        return lhs[0] * rhs[1] - lhs[1] * rhs[0];
    }

    float length(const vec2& vec) {
        return std::sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    }

    // functio vev3 , mat3 , etc.
    vec3 add(const vec3& lhs, const vec3& rhs) {
        return { lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2] };
    }

    vec3 sub(const math::vec3& lhs, const math::vec3& rhs) {
        return { lhs[0] - rhs[0], lhs[1] - rhs[1] , lhs[2] - rhs[2] };
    }

    vec3 mul(float scalar, const math::vec3& vector) {
        return { scalar * vector[0], scalar * vector[1], scalar * vector[2] };
    }

    vec3 div(const math::vec3& vector, float divisor) {

        if (divisor != 0.0f) {
            return { vector[0] / divisor, vector[1] / divisor , vector[2] / divisor };
        }
        else {
            throw std::runtime_error("Error: jakoo nolasta.");
            // palauta alkuperainen vector. 
            return vector;
        }
    }

    // Producto punto de dos vectores
    float dot(const vec3& lhs, const vec3& rhs) {
        return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
    }

    // Calcula la determinante de una matriz 3x3 .Tosi vaekea ymmrt , sain tehty muuta jos kyysy en osa vasta ,jos ei lyt mat blogissa  miss lysi tm ... 
    float det(const mat3& mat) {
        float determinant = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) -
            mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) +
            mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);
        return determinant;
    }

    // Calcula la transposicin de una matriz 3x3
    math::mat3 transpose(const mat3& mat) {
        math::mat3 transposedMatrix;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                transposedMatrix[row][col] = mat[col][row];
            }
        }
        return transposedMatrix;
    }

    // Implementa la funcin de salida para math::mat3
    std::ostream& operator<<(std::ostream& os, const math::mat3& mat) {
        os << "(" << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << ")" << std::endl;
        os << "(" << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << ")" << std::endl;
        os << "(" << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << ")";
        return os;
    }
}





