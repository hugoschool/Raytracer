#include "primitives/Cylinder.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <cmath>
#include <compare>
#include <cstdlib>
#include <iostream>

Raytracer::Cylinder::Cylinder(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
}

Raytracer::HitInfo Raytracer::Cylinder::hits(Raytracer::Ray &ray)
{
    // see https://stackoverflow.com/questions/73866852/ray-cylinder-intersection-formula
    Math::Vector3D D = ray.direction.normalize();
    Math::Vector3D V = _options.cylinderAxis.normalize();
    Math::Vector3D X = ray.origin - _options.center;

    double a = D.dot(D) - std::pow(D.dot(V), 2);
    double b = 2 * (D.dot(X) - (D.dot(V) * X.dot(V)));
    double c = X.dot(X) - std::pow(X.dot(V), 2) - std::pow(_options.radius, 2);

    double d = std::pow(b, 2) - 4 * a * c;

    if (d < 0) {
        return HitInfo(false);
    }
    double k = 0;
    if (d == 0) {
        k = (-b) / (2*a);
    } else {
        // divison par zero
        if (a == 0) {
            return HitInfo(false);
        }
        double k1 = (-b -sqrt(d)) / (2 * a);
        double k2 = (-b +sqrt(d)) / (2 * a);
        k = std::min(std::abs(k1), std::abs(k2));
    }
    Math::Point3D coincide = ray.origin + (D * k);
    // verfiy for finite cylinder
    double projection = (coincide - _options.center).dot(V);
    if (projection < 0 || projection > _options.cylinderAxis.length()) {
        return HitInfo(false);
    }
    return HitInfo(true, coincide, _options.color);
}

Raytracer::Math::Vector3D Raytracer::Cylinder::getNormal(const Math::Point3D point) const
{
    double t = (point - _options.center).dot(_options.cylinderAxis.normalize());
    Math::Point3D axis_point = _options.center + (_options.cylinderAxis.normalize() * t);

    // top hit
    if (std::abs(t - _options.cylinderAxis.length()) < 0 && (point - axis_point).dot(point - axis_point) <= std::pow(_options.radius, 2)) {
        return _options.cylinderAxis.normalize();
    }

    // // bottom hit
    if (std::abs(t) < 0 && (point - axis_point).dot(point - axis_point) <= std::pow(_options.radius, 2)) {
        return _options.cylinderAxis.normalize() * -1;
    }

    // side hit
    return (point - axis_point).normalize();
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Cylinder(options);
}
