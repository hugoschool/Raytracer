#include "Math/Vector3D.hpp"
#include "Math/Matrix3x1.hpp"
#include <cmath>
#include <iostream>

Raytracer::Math::Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

Raytracer::Math::Vector3D::Vector3D(const Matrix3x1 &matrix) : x(matrix.get(0)), y(matrix.get(1)), z(matrix.get(2))
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

void Raytracer::Math::Vector3D::operator*=(const double nb)
{
    this->x *= nb;
    this->y *= nb;
    this->z *= nb;
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


Raytracer::Math::Vector3D Raytracer::Math::Vector3D::operator=(const Matrix3x1 &matrix)
{
    this->x = matrix.get(0);
    this->y = matrix.get(1);
    this->z = matrix.get(2);
    return *this;
}


// https://math.libretexts.org/Bookshelves/Applied_Mathematics/Mathematics_for_Game_Developers_(Burzynski)/04%3A_Matrices/4.06%3A_Rotation_Matrices_in_3-Dimensions
// https://en.wikipedia.org/wiki/Rotation_matrix#In_three_dimensions
Raytracer::Math::Vector3D Raytracer::Math::Vector3D::rotateX(double degree) const
{
    Math::Matrix3x1 vectorMatrix(this->x, this->y, this->z);
    return Vector3D(vectorMatrix.rotateX(degree));
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::rotateY(double degree) const
{
    Math::Matrix3x1 vectorMatrix(this->x, this->y, this->z);
    return Vector3D(vectorMatrix.rotateY(degree));
}

Raytracer::Math::Vector3D Raytracer::Math::Vector3D::rotateZ(double degree) const
{
    Math::Matrix3x1 vectorMatrix(this->x, this->y, this->z);
    return Vector3D(vectorMatrix.rotateZ(degree));
}

double Raytracer::Math::Vector3D::cosine(Vector3D &normal)
{
    double value = this->dot(normal) / (this->length() * normal.length());
    value = std::max(0.0, value);
    return value;
}
