#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Plane.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"

Raytracer::Plane::Plane(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
}

Raytracer::HitInfo Raytracer::Plane::hits(Raytracer::Ray &ray)
{
    double k_vec = 0.0;
    double dot = ray.direction.dot(this->_options.normal);
    if (dot != 0) {
        k_vec = (_options.center - ray.origin).dot(_options.normal) / dot;
    }
    if (k_vec <= 0)
        return HitInfo(false);
    Math::Point3D coincide = ray.origin + (ray.direction * k_vec);
    return HitInfo(true, coincide, _options.color);
}

Raytracer::Math::Vector3D Raytracer::Plane::getNormal(const Math::Point3D) const
{
    return _options.normal;
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Plane(options);
}
