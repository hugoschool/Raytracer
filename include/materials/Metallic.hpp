#pragma once

#include "materials/AMaterial.hpp"
#include "materials/MaterialOptions.hpp"

namespace Raytracer {
    class Metallic : public AMaterial {
        public:
            Metallic() = delete;
            Metallic(MaterialOptions options);
            ~Metallic() = default;
    };
}
