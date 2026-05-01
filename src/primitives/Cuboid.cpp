#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Cuboid.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

Raytracer::Cuboid::Cuboid(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
}

Raytracer::HitInfo Raytracer::Cuboid::hits(Raytracer::Ray &ray)
{
    std::cerr << "x:" << _options.diagonal.x << ", y: " << _options.diagonal.y << ", z: " << _options.diagonal.z << std::endl;
    // std::sleep(1);
    return HitInfo(false);
}

Raytracer::Math::Vector3D Raytracer::Cuboid::getNormal(const Math::Point3D point) const
{
    return point - this->_options.center;
}

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Cuboid(options);
}
