#pragma once

#include "Math/Rectangle3D.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Camera {
        public:
            Camera();
            Camera(const Math::Point3D origin, const Math::Rectangle3D screen);
            ~Camera() = default;

            Math::Point3D origin;
            Math::Rectangle3D screen;

            Raytracer::Ray ray(double u, double v);
    };
}
