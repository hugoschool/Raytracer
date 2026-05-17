#include "primitives/Triangle.hpp"
#include "Exception.hpp"
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Triangle.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"

Raytracer::Triangle::Triangle(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
    if (options.vertices.size() != 3)
        throw Exception("Incorrect amount of vertices for a triangle");

    a = options.vertices[0];
    b = options.vertices[1];
    c = options.vertices[2];

    Math::Vector3D ab = a - b;
    Math::Vector3D ac = a - c;

    this->_normal = ab.cross_product(ac);
    this->_normal = this->_normal / this->_normal.length();
}

//Théorie tirée de cette vidéo youtube https://youtu.be/XgUhgSlQvic
Raytracer::HitInfo Raytracer::Triangle::hits(Raytracer::Ray &ray)
{
    double k_vec = 0.0;
    double dot = ray.direction.dot(this->_normal);
    if (dot != 0) {
        k_vec = (ray.origin - a).dot(_normal) / dot;
    }
    if (k_vec <= 0)
        return HitInfo(false);
    Math::Point3D coincide = ray.origin + (ray.direction * k_vec);
    Math::Vector3D ba = b - a;
    Math::Vector3D cb = c - b;
    Math::Vector3D ac = a - c;
    Math::Vector3D triangle_hit = coincide - a;
    Math::Vector3D orthogonal = ba.cross_product(triangle_hit);
    dot = orthogonal.dot(this->_normal);
    if (orthogonal.dot(this->_normal) <= 0)
        return HitInfo(false);
    triangle_hit = coincide - b;
    orthogonal = cb.cross_product(triangle_hit);
    if (orthogonal.dot(this->_normal) <= 0)
        return HitInfo(false);
    triangle_hit = coincide - c;
    orthogonal = ac.cross_product(triangle_hit);

    if (orthogonal.dot(this->_normal) <= 0)
        return HitInfo(false);
    return HitInfo(true, coincide, _options.color, k_vec);
}

Raytracer::Math::Vector3D Raytracer::Triangle::getNormal(const Math::Point3D) const
{
    return _normal * -1;
}
