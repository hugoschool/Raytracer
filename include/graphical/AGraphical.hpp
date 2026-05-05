#pragma once

#include "graphical/IGraphical.hpp"
#include <cstddef>

namespace Raytracer {
    class AGraphical : public IGraphical {
        public:
            AGraphical(const std::size_t width, const std::size_t height);
            ~AGraphical();

            void handleEvents() override;
            bool isOpen() override;
            void displayPixels(std::vector<std::vector<Pixel>> &) override;

        protected:
            const std::size_t _width;
            const std::size_t _height;
    };
};
