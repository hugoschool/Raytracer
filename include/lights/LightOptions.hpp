#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"

namespace Raytracer {
    struct LightOptions {
        // Globally used
        Color color;

        // Point
        const Math::Point3D position;
    };
}
