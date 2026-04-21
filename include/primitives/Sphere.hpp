#pragma once

#include "Math/Point3D.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Sphere {
        public:
            Sphere(const Math::Point3D &center, double radius);
            ~Sphere() = default;

            Math::Point3D center;
            double radius;

            bool hits(Ray &ray);
    };
}
