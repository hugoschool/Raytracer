#include "Math/Vector3D.hpp"
#include <cmath>
#include <iostream>
Raytracer::Math::Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

double Raytracer::Math::Vector3D::length()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

double Raytracer::Math::Vector3D::dot(Vector3D &vector)
{
    return x * vector.x + y * vector.y + z * vector.z;
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::operator+(const Raytracer::Math::Vector3D &vector) const
{
    return Raytracer::Math::Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::operator-(const Raytracer::Math::Vector3D &vector) const
{
    return Raytracer::Math::Vector3D(x - vector.x, y - vector.y, z - vector.z);
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::operator*(const Raytracer::Math::Vector3D &vector) const
{
    return Raytracer::Math::Vector3D(x * vector.x, y * vector.y, z * vector.z);
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::operator*(const double nb) const
{
    return Raytracer::Math::Vector3D(x * nb, y * nb, z * nb);
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::operator/(const Raytracer::Math::Vector3D &vector) const
{
    if (vector.x == 0 || vector.y == 0 || vector.z == 0) {
        std::cerr << "Floating point exception" << std::endl;
        return Raytracer::Math::Vector3D(*this);
    }
    return Raytracer::Math::Vector3D(x / vector.x, y / vector.y, z / vector.z);
}

void Raytracer::Math::Vector3D::operator+=(const Vector3D &vector)
{
    this->x += vector.x;
    this->y += vector.y;
    this->z += vector.z;
}

void Raytracer::Math::Vector3D::operator-=(const Vector3D &vector)
{
    this->x -= vector.x;
    this->y -= vector.y;
    this->z -= vector.z;
}

void Raytracer::Math::Vector3D::operator*=(const Vector3D &vector)
{
    this->x *= vector.x;
    this->y *= vector.y;
    this->z *= vector.z;
}

void Raytracer::Math::Vector3D::operator/=(const Vector3D &vector)
{
    if (vector.x == 0 || vector.y == 0 || vector.z == 0) {
        std::cerr << "Floating point exception" << std::endl;
        return;
    }
    this->x /= vector.x;
    this->y /= vector.y;
    this->z /= vector.z;
}

// https://math.libretexts.org/Bookshelves/Applied_Mathematics/Mathematics_for_Game_Developers_(Burzynski)/04%3A_Matrices/4.06%3A_Rotation_Matrices_in_3-Dimensions
// https://en.wikipedia.org/wiki/Rotation_matrix#In_three_dimensions
// TODO: could be improved with a matrix class perhaps?
Raytracer::Math::Vector3D Raytracer::Math::Vector3D::rotateX(double degree) const
{
    double matrix[3][3] = {
        {1, 0, 0},
        {0, std::round(std::cos(degree)), std::round(-std::sin(degree))},
        {0, std::round(std::sin(degree)), std::round(std::cos(degree))},
    };

    Raytracer::Math::Vector3D v1 = Raytracer::Math::Vector3D(matrix[0][0], matrix[1][0], matrix[2][0]) * x;
    Raytracer::Math::Vector3D v2 = Raytracer::Math::Vector3D(matrix[0][1], matrix[1][1], matrix[2][1]) * y;
    Raytracer::Math::Vector3D v3 = Raytracer::Math::Vector3D(matrix[0][2], matrix[1][2], matrix[2][2]) * z;

    return v1 + v2 + v3;
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::rotateY(double degree) const
{
    double matrix[3][3] = {
        {std::round(std::cos(degree)), 0, std::round(std::sin(degree))},
        {0, 1, 0},
        {std::round(-std::sin(degree)), 0, std::round(std::cos(degree))},
    };

    Raytracer::Math::Vector3D v1 = Raytracer::Math::Vector3D(matrix[0][0], matrix[1][0], matrix[2][0]) * x;
    Raytracer::Math::Vector3D v2 = Raytracer::Math::Vector3D(matrix[0][1], matrix[1][1], matrix[2][1]) * y;
    Raytracer::Math::Vector3D v3 = Raytracer::Math::Vector3D(matrix[0][2], matrix[1][2], matrix[2][2]) * z;

    return v1 + v2 + v3;
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::rotateZ(double degree) const
{
    double matrix[3][3] = {
        {std::round(std::cos(degree)), std::round(-std::sin(degree)), 0},
        {std::round(std::sin(degree)), std::round(std::cos(degree)), 0},
        {0, 0, 1},
    };

    Raytracer::Math::Vector3D v1 = Raytracer::Math::Vector3D(matrix[0][0], matrix[1][0], matrix[2][0]) * x;
    Raytracer::Math::Vector3D v2 = Raytracer::Math::Vector3D(matrix[0][1], matrix[1][1], matrix[2][1]) * y;
    Raytracer::Math::Vector3D v3 = Raytracer::Math::Vector3D(matrix[0][2], matrix[1][2], matrix[2][2]) * z;

    return v1 + v2 + v3;
}
