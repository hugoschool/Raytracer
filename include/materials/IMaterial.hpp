#pragma once

#include "materials/MaterialOptions.hpp"
namespace Raytracer {
    class IMaterial {
        public:
            virtual ~IMaterial() = default;

            virtual MaterialOptions getOptions() const = 0;
            // TODO
    };
}
