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

        private:
            LightOptions _options;
    };
}
