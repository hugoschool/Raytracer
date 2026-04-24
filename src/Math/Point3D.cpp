#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

Raytracer::Math::Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

Raytracer::Math::Point3D Raytracer::Math::Point3D::operator+(const Point3D &point) const
{
    return Raytracer::Math::Point3D(x + point.x, y + point.y, z + point.z);
}

Raytracer::Math::Vector3D Raytracer::Math::Point3D::operator-(const Point3D &point) const
{
    return Raytracer::Math::Vector3D(x - point.x, y - point.y, z - point.z);
}

Raytracer::Math::Point3D Raytracer::Math::Point3D::operator+(const Vector3D &vec) const
{
    return Raytracer::Math::Point3D(x + vec.x, y + vec.y, z + vec.z);
}

bool Raytracer::Math::Point3D::operator==(const Point3D &other) const
{
    return (this->x == other.x && this->y == other.y && this->z == other.z);
}

