#pragma once

#include "Color.hpp"

namespace Raytracer {
    struct MaterialProperties {
        double transparency;
        double reflexion;
        double refraction;
    };
    struct MaterialOptions {
        // Globally used
        Color color;
        // Set by the constructor of the material itself
        MaterialProperties properties;
    };
}
