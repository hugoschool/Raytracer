#pragma once

#include "lights/LightOptions.hpp"

namespace Raytracer {
    class ILight {
        public:
            virtual ~ILight() = default;

            virtual LightOptions getOptions() const = 0;
    };
}
