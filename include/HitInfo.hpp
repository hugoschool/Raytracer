#pragma once
#include "Color.hpp"
#include "Math/Point3D.hpp"
namespace Raytracer {
    class HitInfo {
        public:
            HitInfo() = default;
            HitInfo(bool, Math::Point3D &, Color &);
            HitInfo(bool);
            ~HitInfo() = default;
            bool hasHit() const;
            Math::Point3D getHitPos() const;
            Color getColor() const;
        private:
        bool _hasHit;
        Math::Point3D _hitPos;
        Color _color;
    };
}