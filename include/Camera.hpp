#pragma once

#include "Math/Vector3D.hpp"
#include "Screen.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Camera {
        public:
            Camera();
            Camera(const Math::Point3D origin, const Screen screen,
                const std::size_t width, const std::size_t height,
                Math::Vector3D direction = Math::Vector3D(0, 0, 0));
            ~Camera() = default;

            Math::Point3D origin;
            Screen screen;
            std::size_t width;
            std::size_t height;
            Math::Vector3D direction;

            Raytracer::Ray ray(double u, double v);
    };
}
