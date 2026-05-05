#pragma once

#include "Color.hpp"

namespace Raytracer {
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void putPixel(Raytracer::Color color) = 0;
    };
}
