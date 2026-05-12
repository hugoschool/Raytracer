#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include <cstddef>

namespace Raytracer {
    class Screen {
        public:
            Screen();
            Screen(const std::size_t width, const std::size_t height, const double fov = 0.0,
                const Math::Point3D cameraOrigin = Math::Point3D());
            ~Screen() = default;

            Math::Point3D origin;
            Math::Vector3D leftSide;
            Math::Vector3D bottomSide;

            Math::Point3D pointAt(double u, double v);
    };
}
