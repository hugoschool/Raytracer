#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Vector3D.hpp"
#include <vector>

namespace Raytracer {
    struct PrimitiveOptions {
        // Globally used
        const Math::Point3D center;
        Color color;

        // Sphere
        double radius;
        // Plane
        const Math::Vector3D normal;
        // Triangle
        std::vector<Math::Point3D> vertices;
        // Cylinder
        Math::Vector3D cylinderAxis;
    };
}
