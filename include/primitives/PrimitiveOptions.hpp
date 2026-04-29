#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "materials/IMaterial.hpp"
#include <memory>

namespace Raytracer {
    enum class PlaneAxis {
        None,
        X,
        Y,
        Z
    };
    struct PrimitiveOptions {
        // Globally used
        const Math::Point3D center;
        Color color;
        std::shared_ptr<IMaterial> material;

        // Sphere
        double radius;
        // Plane
        PlaneAxis axis;
        long long position;
    };
}
