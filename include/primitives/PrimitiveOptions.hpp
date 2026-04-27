#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include <string>

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
    };
}
