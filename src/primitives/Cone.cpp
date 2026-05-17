#include "primitives/Cone.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <cmath>
#include <cstdlib>

Raytracer::Cone::Cone(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
}

Raytracer::HitInfo Raytracer::Cone::hits(Raytracer::Ray &ray)
{
    Math::Vector3D D = ray.direction.normalize();
    Math::Vector3D V = _options.cylinderAxis.normalize();
    Math::Vector3D X = _options.center - ray.origin;
    double m = _options.radius;
    double dv = D.dot(V);
    double xv = X.dot(V);
    double a = dv * dv - m * m * D.dot(D);
    double b = 2.0 * (xv * dv - m * m * X.dot(D));
    double c = xv * xv - m * m * X.dot(X);
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0 || a == 0.0)
        return HitInfo(false);
    double k1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double k2 = (-b + sqrt(discriminant)) / (2.0 * a);
    double candidates[2] = { k1, k2 };
    if (candidates[0] > candidates[1])
        std::swap(candidates[0], candidates[1]);
    for (double k : candidates) {
        if (k < 0.0)
            continue;
        Math::Point3D coincide = ray.origin + (D * k);
        Math::Vector3D P = _options.center - coincide;
        if (P.dot(V) < 0.0)
            continue;
        return HitInfo(true, coincide, _options.color);
    }
    return HitInfo(false);
}

Raytracer::Math::Vector3D Raytracer::Cone::getNormal(const Math::Point3D point) const
{
    Math::Vector3D V = _options.cylinderAxis.normalize();
    Math::Vector3D P = _options.center - point;
    double m = _options.radius;
    double pv = P.dot(V);
    Math::Vector3D normal = V * pv - P * (m * m);
    return normal.normalize();
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Cone(options);
}