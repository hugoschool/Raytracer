#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Cube.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>

Raytracer::Cube::Cube(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
}

Raytracer::HitInfo Raytracer::Cube::hits(Raytracer::Ray &ray)
{
    double k;
    Math::Point3D coincide;
    double half = _options.length;
    Math::Point3D bmin(_options.center.x - half, _options.center.y - half, _options.center.z - half);
    Math::Point3D bmax(_options.center.x + half, _options.center.y + half, _options.center.z + half);
    double tx1 = (bmin.x - ray.origin.x) / ray.direction.x;
    double tx2 = (bmax.x - ray.origin.x) / ray.direction.x;
    double ty1 = (bmin.y - ray.origin.y) / ray.direction.y;
    double ty2 = (bmax.y - ray.origin.y) / ray.direction.y;
    double tz1 = (bmin.z - ray.origin.z) / ray.direction.z;
    double tz2 = (bmax.z - ray.origin.z) / ray.direction.z;
    double tmin = std::max({std::min(tx1, tx2), std::min(ty1, ty2), std::min(tz1, tz2)});
    double tmax = std::min({std::max(tx1, tx2), std::max(ty1, ty2), std::max(tz1, tz2)});

    if (tmax < 0 || tmin > tmax)
        return HitInfo(false);
    k = tmin > 0 ? tmin : tmax;
    coincide = ray.origin + (ray.direction * k);
    return HitInfo(true, coincide, _options.color, k);
}

Raytracer::Math::Vector3D Raytracer::Cube::getNormal(const Math::Point3D point) const
{
    double half = _options.length;
    Math::Vector3D local = point - this->_options.center;
    Math::Vector3D normal(0, 0, 0);
    double epsilon = 1e-4;

    if (std::abs(std::abs(local.x) - half) < epsilon)
        normal = Math::Vector3D(local.x > 0 ? 1 : -1, 0, 0);
    else if (std::abs(std::abs(local.y) - half) < epsilon)
        normal = Math::Vector3D(0, local.y > 0 ? 1 : -1, 0);
    else if (std::abs(std::abs(local.z) - half) < epsilon)
        normal = Math::Vector3D(0, 0, local.z > 0 ? 1 : -1);
    return normal;
}
