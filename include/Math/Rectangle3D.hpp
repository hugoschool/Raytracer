#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <cstddef>

namespace Raytracer {
    namespace Math {
        class Rectangle3D {
            public:
                Rectangle3D();
                Rectangle3D(const std::size_t width, const std::size_t height, const double fov = 0.0);
                ~Rectangle3D() = default;

                Point3D origin;
                Vector3D leftSide;
                Vector3D bottomSide;

                Point3D pointAt(double u, double v);
        };
    }
}
