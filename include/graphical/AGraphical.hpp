#pragma once

#include "graphical/IGraphical.hpp"

namespace Raytracer {
    class AGraphical : public IGraphical {
        public:
            AGraphical();
            ~AGraphical();

            void putPixel(Raytracer::Color color) override;
    };
};
