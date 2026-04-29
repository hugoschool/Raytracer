#pragma once

#include "materials/AMaterial.hpp"
#include "materials/MaterialOptions.hpp"

namespace Raytracer {
    class FlatColor : public AMaterial {
        public:
            FlatColor() = delete;
            FlatColor(MaterialOptions options);
            ~FlatColor() = default;
    };
}
