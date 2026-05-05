#pragma once

#include "Pixel.hpp"
#include <vector>

namespace Raytracer {
    class IGraphical {
        public:
            virtual ~IGraphical() = default;

            virtual void handleEvents() = 0;
            virtual bool isOpen() = 0;
            virtual void displayPixels(std::vector<std::vector<Pixel>> &) = 0;
    };
}
