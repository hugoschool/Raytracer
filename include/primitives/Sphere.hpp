#pragma once

#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "primitives/IPrimitive.hpp"

namespace Raytracer {
    class Sphere : public IPrimitive{
        public:
            Sphere(const Math::Point3D &center, double radius, Color color);
            ~Sphere() = default;

            Math::Point3D center;
            double radius;
            Color color;

            HitInfo hits(Ray &ray);
            Color getColor(Ray &ray) const;
            Math::Vector3D getNormal(const Math::Point3D &) const;
    };
}
