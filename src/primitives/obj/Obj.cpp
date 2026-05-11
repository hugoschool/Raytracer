#include "primitives/Obj.hpp"
#include "Exception.hpp"
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Obj.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <iostream>

Raytracer::Obj::Obj(Raytracer::PrimitiveOptions options) : APrimitive(options)
{
    std::cerr << options.fileName << std::endl;
}

Raytracer::HitInfo Raytracer::Obj::hits(Raytracer::Ray &ray)
{
    return HitInfo(false);
}

Raytracer::Math::Vector3D Raytracer::Obj::getNormal(const Math::Point3D) const
{
    return Math::Vector3D(0, 0, 0);
}
