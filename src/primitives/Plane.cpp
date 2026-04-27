#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Plane.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <iostream>

Raytracer::Plane::Plane(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
}

Raytracer::HitInfo Raytracer::Plane::hits(Raytracer::Ray &ray)
{
    if (ray.direction.dot(this->getNormal(Math::Point3D(0,0,0))) == 0) {
        return HitInfo(false);
    }

    double k_vec = 0.0;
    // std::cerr <<"x, y, z: " << this->_options.center.x << " " << this->_options.center.y << " " << this->_options.center.z << std::endl;
    if (this->_options.center.x != 0 && ray.direction.x != 0)
        k_vec = (this->_options.center.x - ray.origin.x) / ray.direction.x;
    else if (this->_options.center.y != 0 && ray.direction.y != 0)
        k_vec = (this->_options.center.y - ray.origin.y) / ray.direction.y;
    else if (this->_options.center.z != 0 && ray.direction.z != 0)
        k_vec = (this->_options.center.z - ray.origin.z) / ray.direction.z;
    else 
        return HitInfo(false);
    if (k_vec < 0)
        return HitInfo(false);
    Math::Point3D coincide = ray.origin + (ray.direction * k_vec);
    // std::cerr << "got coincide x, y, z: " << coincide.x << " " << coincide.y << " " << coincide.z << std::endl;

    return HitInfo(true, coincide, _options.color);
}

Raytracer::Math::Vector3D Raytracer::Plane::getNormal(const Math::Point3D point) const
{
    // TODO: penser à une manière plus joli de faire ça pcq là je suis geeked sa mère
    Math::Vector3D normal;
    if (this->_options.center.x != 0)
        normal = Math::Vector3D(0, 1, 1);
    else if (this->_options.center.y != 0)
        normal = Math::Vector3D(1, 0, 1);
    else if (this->_options.center.z != 0)
        normal = Math::Vector3D(1, 1, 0);
    else
        normal = Math::Vector3D(0,0,0);
    // std::cerr <<"x, y, z: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
    return normal;    
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Plane(options);
}
