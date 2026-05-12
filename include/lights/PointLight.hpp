#pragma once

#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

namespace Raytracer {
    class PointLight : public ALight {
        public:
            PointLight() = delete;
            PointLight(LightOptions options);
            ~PointLight() = default;

            Math::Vector3D getDirection(Math::Point3D) const override;
    };
}
