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
            Ray getRay(Math::Vector3D &, HitInfo &) const override;
            void modifyMultiplierForShadow(Math::Vector3D, Math::Vector3D, double &, double) const override;
    };
}
