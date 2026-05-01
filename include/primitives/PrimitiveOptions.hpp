#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    enum class PlaneAxis {
        None,
        X,
        Y,
        Z
    };
    struct PrimitiveOptions {
        // Globally used
        const Math::Point3D center;
        Color color;

        // Sphere
        double radius;
        // Plane
        PlaneAxis axis;
        long long position;
        // Cuboid
        Math::Vector3D diagonal;
        // Cylinder
        Math::Vector3D cylinderAxis;
    };
}
