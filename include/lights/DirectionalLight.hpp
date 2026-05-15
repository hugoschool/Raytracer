#pragma once

#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

namespace Raytracer {
    class DirectionalLight : public ALight {
        public:
            DirectionalLight() = delete;
            DirectionalLight(LightOptions options);
            ~DirectionalLight() = default;

            Math::Vector3D getDirection(Math::Point3D) const override;
            void modifyMultiplierForShadow(Math::Vector3D, Math::Vector3D, double &, double) const override;
    };
}
