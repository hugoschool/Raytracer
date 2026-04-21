#include "Math/Rectangle3D.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>
#include <iostream>

Raytracer::Math::Rectangle3D::Rectangle3D() : origin(-200, -200, -10), leftSide(0, 400, 0), bottomSide(400, 0, 0)
{
}

Raytracer::Math::Rectangle3D::Rectangle3D(const std::size_t width, const std::size_t height, const double fov) :
    origin(-(static_cast<double>(width) / 2), -(static_cast<double>(height) / 2), -10), // TODO: change Z for FOV
    leftSide(0, height, 0), bottomSide(width, 0, 0)
{
    // d = 200/tan(fov/2), avec d la distance entre la caméra et le plan

    double d = width/(std::tan(fov) * 2);
    d = pow(d, 2);
    d = d/2;
    d = std::sqrt(d);
    origin = Point3D(-d, -d, -d);
    // std::cerr << "d: " << d << "   tan(fov): " << std::tan(fov) << std::endl;;
}

Raytracer::Math::Point3D Raytracer::Math::Rectangle3D::pointAt(double u, double v)
{
    Vector3D leftVector = leftSide * u;
    Vector3D bottomVector = bottomSide * v;

    return origin + leftVector + bottomVector;
}
