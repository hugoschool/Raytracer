#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Sphere.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <cmath>
#include <cstdlib>

Raytracer::Sphere::Sphere(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
}

// From the bootstrap:
//
// Not explained in the bootstrap:
// a, b, c comes from the "written down" / "expanded" version of the quadratic equation.
//
// x^2 = (OxK) ^ 2 + 2OxKDxK + DxK^2
// Same for y^2 and z^2 (https://en.wikipedia.org/wiki/Quadratic_equation)
//
// a * k^2 = (OxK) ^ 2 + (OyK) ^ 2 + (OzK) ^ 2
// b * k = 2DxKOx + 2DyOy + 2DzKOz
// c (the rest) = Ox^2 + Oy^2 + Oz^2 - R^2
//
// Remove the all references to k
//
// This only works for a Sphere who's origin is 0, 0, 0
// To remedy this:
// O = Sphere Center - Ray Origin
//
Raytracer::HitInfo Raytracer::Sphere::hits(Raytracer::Ray &ray)
{
    Math::Vector3D centerOffset = _options.center - ray.origin;
    double a = ray.direction.dot(ray.direction);
    double b = 2 * ray.direction.x * centerOffset.x + 2 * ray.direction.y * centerOffset.y + 2 * ray.direction.z * centerOffset.z;
    double c = centerOffset.dot(centerOffset) - std::pow(_options.radius, 2);
    double d = std::pow(b, 2) - 4 * a * c;

    if (d < 0) {
        return HitInfo(false);
    }
    double k = 0;
    if (d == 0) {
        k = (-b) / (2*a);
    } else {
        double k1 = (-b -sqrt(d)) / (2 * a);
        double k2 = (-b +sqrt(d)) / (2 * a);
        k = std::min(std::abs(k1), std::abs(k2));
    }
    Math::Point3D coincide = ray.origin + (ray.direction * k);
    return HitInfo(true, coincide, _options.color);
}

Raytracer::Math::Vector3D Raytracer::Sphere::getNormal(const Math::Point3D point) const
{
    return point - _options.center;
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Sphere(options);
}
