#pragma once

#include "materials/AMaterial.hpp"
#include "materials/MaterialOptions.hpp"

namespace Raytracer {
    class Transparent : public AMaterial {
        public:
            Transparent() = delete;
            Transparent(MaterialOptions options);
            ~Transparent() = default;
    };
}
