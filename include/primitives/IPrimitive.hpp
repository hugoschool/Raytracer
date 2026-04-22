#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Ray.hpp"
#include "primitives/PrimitiveOptions.hpp"

namespace Raytracer {
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;

            virtual HitInfo hits(Ray &ray) = 0;
            virtual PrimitiveOptions getOptions() const = 0;
            virtual Math::Vector3D getNormal(Math::Point3D) const = 0;
            // TODO: getMaterial
    };
}
