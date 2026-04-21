#pragma once

#include "Vector3D.hpp"

namespace Raytracer {
    namespace Math {
        class Point3D {
            public:
                Point3D() = default;
                Point3D(double x, double y, double z);
                ~Point3D() = default;

                Point3D operator+(const Point3D &) const;
                Vector3D operator-(const Point3D &) const;

                Point3D operator+(const Vector3D &) const;

                double x;
                double y;
                double z;
        };
    }
}
