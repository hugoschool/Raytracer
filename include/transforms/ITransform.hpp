#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class ITransform {
        public:
            virtual ~ITransform() = default;

            virtual void transformVector(Math::Vector3D &) = 0;
            virtual void transformPoint(Math::Point3D &) = 0;
    };
}
