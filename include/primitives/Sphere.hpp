#pragma once

#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "IPrimitive.hpp"

namespace Raytracer {
    class Sphere : public IPrimitive {
        public:
            Sphere(const Math::Point3D &center, double radius, Color color);
            ~Sphere() = default;

            HitInfo hits(Ray &ray) override;
            Color getColor(Ray &ray) const override;
            Math::Vector3D getNormal(const Math::Point3D) const override;
            const Math::Point3D getCenter() const override;

        private:
            Math::Point3D _center;
            double _radius;
            Color _color;
    };
}
