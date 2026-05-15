#pragma once

#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

namespace Raytracer {
    class AmbientLight : public ALight {
        public:
            AmbientLight() = delete;
            AmbientLight(LightOptions options);
            ~AmbientLight() = default;

            Math::Vector3D getDirection(Math::Point3D) const override;
            void modifyMultiplierForShadow(Math::Vector3D, Math::Vector3D, double &, double) const override;
    };
}
