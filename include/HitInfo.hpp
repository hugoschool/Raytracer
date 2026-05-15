#pragma once
#include "Color.hpp"
#include "Math/Point3D.hpp"
namespace Raytracer {
    class HitInfo {
        public:
            HitInfo() = default;
            HitInfo(bool, Math::Point3D &, Color &, double);
            HitInfo(bool);
            ~HitInfo() = default;
            bool hasHit() const;
            Math::Point3D getHitPos() const;
            Color getColor() const;
            double getMultiplier() const;

        private:
            bool _hasHit;
            Math::Point3D _hitPos;
            Color _color;
            double _multiplier;
    };
}
