#pragma once

#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

namespace Raytracer {
    class PointLight : public ALight {
        public:
            PointLight() = delete;
            PointLight(LightOptions options);
            ~PointLight() = default;
    };
}
