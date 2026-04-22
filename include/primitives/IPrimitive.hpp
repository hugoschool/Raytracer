#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"

namespace Raytracer {
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;

            virtual HitInfo hits(Ray &ray) = 0;
            virtual Color getColor(Ray &ray) const = 0;
            virtual Math::Vector3D getNormal(Math::Point3D) const = 0;
            // TODO: getMaterial

            virtual const Math::Point3D getCenter() const = 0;
    };
}
