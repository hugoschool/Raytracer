#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"

namespace Raytracer {
    struct LightOptions {
        // Globally used
        const Math::Point3D position;
        Color color;
    };
}
