#include "Ray.hpp"

Raytracer::Ray::Ray(const Math::Point3D &point, const Math::Vector3D &vector) :
    origin(point.x, point.y, point.z), direction(vector.x, vector.y, vector.z)
{
}
