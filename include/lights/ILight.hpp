#pragma once

#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include "lights/LightOptions.hpp"

namespace Raytracer {
    class ILight {
        public:
            virtual ~ILight() = default;

            virtual LightOptions getOptions() const = 0;
            virtual Math::Vector3D getDirection(Math::Point3D) const = 0;
            virtual Ray getRay(Math::Vector3D &, HitInfo &) const = 0;
            virtual bool skipHitDetection() const = 0;
            virtual void modifyMultiplierForShadow(Math::Vector3D, Math::Vector3D, double &, double) const = 0;
    };
}
