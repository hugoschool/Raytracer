#pragma once
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Cone : public APrimitive {
    public:
        Cone(PrimitiveOptions options);
        HitInfo hits(Ray &ray) override;
        Math::Vector3D getNormal(const Math::Point3D point) const override;
    };
}
