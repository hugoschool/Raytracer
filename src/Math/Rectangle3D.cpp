#include "Math/Rectangle3D.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

Raytracer::Math::Rectangle3D::Rectangle3D() : origin(-200, -200, -10), leftSide(0, 400, 0), bottomSide(400, 0, 0)
{
}

Raytracer::Math::Point3D Raytracer::Math::Rectangle3D::pointAt(double u, double v)
{
    Vector3D leftVector = leftSide * u;
    Vector3D bottomVector = bottomSide * v;

    return origin + leftVector + bottomVector;
}
