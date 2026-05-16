#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/PrimitiveOptions.hpp"

namespace Raytracer {
    struct PrimitiveOptions;
    class ITransform {
        public:
            virtual ~ITransform() = default;

            virtual void transform(Math::Vector3D &) = 0;
            virtual void transform(Math::Point3D &) = 0;
            virtual void transform(PrimitiveOptions &) = 0;
    };
}
