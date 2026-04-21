#include "Math/Matrix3x1.hpp"
#include "Math/Matrix3x3.hpp"
#include "Math/Vector3D.hpp"
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>

Raytracer::Math::Matrix3x1::Matrix3x1()
{
    this->_matrix = {0, 0, 0};
}

Raytracer::Math::Matrix3x1::Matrix3x1(double a, double b, double c)
{
    this->_matrix = {a, b, c};
}

Raytracer::Math::Matrix3x1::Matrix3x1(Raytracer::Math::Vector3D &vector)
{
    this->_matrix = {vector.x, vector.y, vector.z};
}

Raytracer::Math::Matrix3x1::Matrix3x1(std::array<double, 3> &arr) : _matrix(arr)
{
}

Raytracer::Math::Matrix3x1 Raytracer::Math::Matrix3x1::rotateX(double angle)
{
    Raytracer::Math::Matrix3x3 Rotation_matrix(
        1, 0, 0,
        0, std::round(std::cos(angle)), std::round(-std::sin(angle)),
        0, std::round(std::sin(angle)), std::round(std::cos(angle))
    );
    return Rotation_matrix * *this;
}

Raytracer::Math::Matrix3x1 Raytracer::Math::Matrix3x1::rotateY(double angle)
{
    Matrix3x3 Rotation_matrix(
        std::round(std::cos(angle)), 0, std::round(std::sin(angle)),
        0, 1, 0,
        std::round(-std::sin(angle)), 0, std::round(std::cos(angle))
    );
    return Rotation_matrix * *this;
}

Raytracer::Math::Matrix3x1 Raytracer::Math::Matrix3x1::rotateZ(double angle)
{
    Matrix3x3 Rotation_matrix(
        std::round(std::cos(angle)), std::round(-std::sin(angle)), 0,
        std::round(std::sin(angle)), std::round(std::cos(angle)), 0,
        0, 0, 1
    );
    return Rotation_matrix * *this;
}

double Raytracer::Math::Matrix3x1::get(size_t y)
{
    if (y >= this->_matrix.size()) {
        std::cerr << "Out of bound reach on matrix" << std::endl;
        return 0;
    }
    return _matrix[y];
}