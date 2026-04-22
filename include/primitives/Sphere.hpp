#pragma once

#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Sphere {
        public:
            Sphere(const Math::Point3D &center, double radius, Color color);
            ~Sphere() = default;

            Math::Point3D center;
            double radius;
            Color color;

            bool hits(Ray &ray);
            Color getColor(Ray &ray) const;
    };
}
