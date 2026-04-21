#include "Math/Matrix.hpp"
#include "Math/Vector3D.hpp"
#include <array>
#include <cmath>

Raytracer::Math::Matrix3x3::Matrix3x3()
{
    this->_matrix[0] = {0, 0, 0};
    this->_matrix[1] = {0, 0, 0};
    this->_matrix[2] = {0, 0, 0};
}

Raytracer::Math::Matrix3x3::Matrix3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i)
{
    this->_matrix[0] = {a, b, c};
    this->_matrix[1] = {d, e, f};
    this->_matrix[2] = {g, h, i};
}

Raytracer::Math::Matrix3x3::Matrix3x3(Raytracer::Math::Vector3D &vector)
{
    this->_matrix[0] = {vector.x, 0, 0};
    this->_matrix[1] = {0, vector.y, 0};
    this->_matrix[2] = {0, 0, vector.z};
}

Raytracer::Math::Matrix3x3::Matrix3x3(std::array<std::array<double, 3>, 3> &arr) : _matrix(arr)
{
}

Raytracer::Math::Matrix3x3 Raytracer::Math::Matrix3x3::operator*(Matrix3x3 &other)
{
    std::array<std::array<double, 3>, 3> result;

    for (std::size_t i = 0; i < 3; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }
    return Matrix3x3(result);
}

Raytracer::Math::Matrix3x3 Raytracer::Math::Matrix3x3::rotateX(double angle)
{
    Matrix3x3 Rotation_matrix(
        1, 0, 0,
        0, std::round(std::cos(angle)), std::round(-std::sin(angle)),
        0, std::round(std::sin(angle)), std::round(std::cos(angle))
    );
    return *this * Rotation_matrix;
}

Raytracer::Math::Matrix3x3 Raytracer::Math::Matrix3x3::rotateY(double angle)
{
    Matrix3x3 Rotation_matrix(
        std::round(std::cos(angle)), 0, std::round(std::sin(angle)),
        0, 1, 0,
        std::round(-std::sin(angle)), 0, std::round(std::cos(angle))
    );
    return *this * Rotation_matrix;
}

Raytracer::Math::Matrix3x3 Raytracer::Math::Matrix3x3::rotateZ(double angle)
{
    Matrix3x3 Rotation_matrix(
        std::round(std::cos(angle)), std::round(-std::sin(angle)), 0,
        std::round(std::sin(angle)), std::round(std::cos(angle)), 0,
        0, 0, 1
    );
    return *this * Rotation_matrix;
}