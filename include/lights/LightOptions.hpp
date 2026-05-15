#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    struct LightOptions {
        // Globally used
        Color color;

        // Point
        Math::Point3D position;

        // Directional
        const Math::Vector3D direction;
    };
}
