#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"

namespace Raytracer {
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;

            HitInfo hits(Raytracer::Ray &ray);
            Math::Vector3D getNormal(Math::Point3D &) const;
    };
}
