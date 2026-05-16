#pragma once

#include "transforms/ITransform.hpp"
#include <memory>

namespace Raytracer {
    struct TransformOptions {
        std::shared_ptr<ITransform> ptr;
        // Scale
        double multiplier;
        // Translate
        Math::Point3D translate;
    };
}
