#include "Math/Rectangle3D.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>
#include <iostream>

Raytracer::Math::Rectangle3D::Rectangle3D() : origin(-200, -200, -10), leftSide(0, 400, 0), bottomSide(400, 0, 0)
{
}

Raytracer::Math::Rectangle3D::Rectangle3D(const std::size_t width, const std::size_t height, const double fov,
    const Math::Point3D cameraOrigin)
{
    const double aspectRatio = static_cast<double>(width) / height;

    const double distanceScreen = 15.0; // also known as focal distance
    const double theta = fov * M_PI / 180.0;
    const double h = 2 * distanceScreen * std::tan(theta / 2);
    const double w = h / aspectRatio;

    origin = Math::Point3D(-(w / 2) + cameraOrigin.x, -(h / 2) + cameraOrigin.y, -distanceScreen + cameraOrigin.z);
    leftSide = Math::Vector3D(0, h, 0);
    bottomSide = Math::Vector3D(w, 0, 0);
}

Raytracer::Math::Point3D Raytracer::Math::Rectangle3D::pointAt(double u, double v)
{
    Vector3D bottomVector = bottomSide * u;
    Vector3D leftVector = leftSide - leftSide * v;

    return origin + leftVector + bottomVector;
}
