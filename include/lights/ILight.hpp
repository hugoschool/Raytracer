#pragma once

#include "Math/Point3D.hpp"
#include "lights/LightOptions.hpp"

namespace Raytracer {
    class ILight {
        public:
            virtual ~ILight() = default;

            virtual LightOptions getOptions() const = 0;
            virtual Math::Vector3D getDirection(Math::Point3D) const = 0;
    };
}
