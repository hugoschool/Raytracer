#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    struct PrimitiveOptions {
        // Globally used
        const Math::Point3D center;
        Color color;
        
        // Sphere
        double radius;
    };
}
