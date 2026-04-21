#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    namespace Math {
        class Rectangle3D {
            public:
                Rectangle3D();
                ~Rectangle3D() = default;

                Point3D origin;
                Vector3D leftSide;
                Vector3D bottomSide;

                Point3D pointAt(double u, double v);
        };
    }
}
