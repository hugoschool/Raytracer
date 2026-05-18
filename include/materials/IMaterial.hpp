#pragma once

#include "Math/Point3D.hpp"
#include "materials/MaterialOptions.hpp"
namespace Raytracer {
    class IMaterial {
        public:
            virtual ~IMaterial() = default;

            virtual MaterialOptions getOptions() const = 0;
            virtual Color applyMaterial(Color, Math::Point3D) const = 0;
    };
}
