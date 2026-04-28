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
    if (ray.direction.dot(this->getNormal(Math::Point3D(0,0,0))) == 0) {
        return HitInfo(false);
    }

    double k_vec = 0.0;
    if (_options.axis == PlaneAxis::X && ray.direction.x != 0) {
        k_vec = (this->_options.position - ray.origin.x) / ray.direction.x;
    } else if (_options.axis == PlaneAxis::Y && ray.direction.y != 0) {
        k_vec = (this->_options.position - ray.origin.y) / ray.direction.y;
    } else if (_options.axis == PlaneAxis::Z && ray.direction.z != 0) {
        k_vec = (this->_options.position - ray.origin.z) / ray.direction.z;
    } else
        return HitInfo(false);
    if (k_vec <= 0)
        return HitInfo(false);
    Math::Point3D coincide = ray.origin + (ray.direction * k_vec);
    return HitInfo(true, coincide, _options.color);
}

Raytracer::Math::Vector3D Raytracer::Plane::getNormal(const Math::Point3D) const
{
    Math::Vector3D normal;

    switch (this->_options.axis) {
        case Raytracer::PlaneAxis::X:
            normal = Math::Vector3D(-1, 0, 0);
            break;
        case Raytracer::PlaneAxis::Y:
            normal = Math::Vector3D(0, -1, 0);
            break;
        case Raytracer::PlaneAxis::Z:
            normal = Math::Vector3D(0, 0, -1);
            break;
        default:
            normal = Math::Vector3D(0,0,0);
    }
    return normal;
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Plane(options);
}
