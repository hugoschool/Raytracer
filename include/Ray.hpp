#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class Ray {
        public:
            Ray() = default;
            Ray(const Math::Point3D &point, const Math::Vector3D &vector);
            ~Ray() = default;

            Math::Point3D origin;
            Math::Vector3D direction;
    };
}
