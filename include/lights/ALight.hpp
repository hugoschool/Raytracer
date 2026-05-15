#pragma once

#include "lights/ILight.hpp"
#include "lights/LightOptions.hpp"

namespace Raytracer {
    class ALight : public ILight {
        public:
            ALight() = delete;
            ALight(LightOptions options);
            ~ALight() = default;

            LightOptions getOptions() const override;
            Math::Vector3D getDirection(Math::Point3D) const override;
            void modifyMultiplierForShadow(Math::Vector3D, Math::Vector3D, double &, double) const override;

        protected:
            LightOptions _options;
    };
}
