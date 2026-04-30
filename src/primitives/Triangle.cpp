#include "primitives/Triangle.hpp"
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Triangle.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <iostream>

Raytracer::Triangle::Triangle(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
    // à noter que _options.normal ne compte pas comme la normale du triangle
    Math::Vector3D ab = this->_options.a - this->_options.b;
    Math::Vector3D ac = this->_options.a - this->_options.c;

    this->_normal = ab.cross_product(ac);
    this->_normal = this->_normal / this->_normal.length();
}

//Théorie tirée de cette vidéo youtube https://youtu.be/XgUhgSlQvic
Raytracer::HitInfo Raytracer::Triangle::hits(Raytracer::Ray &ray)
{
    double k_vec = 0.0;
    double dot = ray.direction.dot(this->_normal);
    if (dot != 0) {
        k_vec = (ray.origin - this->_options.a).dot(_normal) / dot;
    }
    if (k_vec <= 0)
        return HitInfo(false);
    Math::Point3D coincide = ray.origin + (ray.direction * k_vec);

    Math::Vector3D ba = this->_options.b - this->_options.a;
    Math::Vector3D cb = this->_options.c - this->_options.b;
    Math::Vector3D ac = this->_options.a - this->_options.c;
    Math::Vector3D triangle_hit = coincide - this->_options.a;
    Math::Vector3D orthogonal = ba.cross_product(triangle_hit);
    dot = orthogonal.dot(this->_normal);
    if (orthogonal.dot(this->_normal) <= 0)
        return HitInfo(false);
    triangle_hit = coincide - this->_options.b;
    orthogonal = cb.cross_product(triangle_hit);
    if (orthogonal.dot(this->_normal) <= 0)
        return HitInfo(false);
    triangle_hit = coincide - this->_options.c;
    orthogonal = ac.cross_product(triangle_hit);

    if (orthogonal.dot(this->_normal) <= 0)
        return HitInfo(false);

    return HitInfo(true, coincide, _options.color);
}

Raytracer::Math::Vector3D Raytracer::Triangle::getNormal(const Math::Point3D) const
{
    return _normal;
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Triangle(options);
}
