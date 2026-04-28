#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"

namespace Raytracer {
    class Triangle : public APrimitive {
        public:
            Triangle(PrimitiveOptions options);
            ~Triangle() = default;

            HitInfo hits(Ray &ray) override;
            Math::Vector3D getNormal(const Math::Point3D) const override;
    };
}
