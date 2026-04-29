#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Vector3D.hpp"
#include <vector>
#include "materials/IMaterial.hpp"
#include <memory>

namespace Raytracer {
    struct PrimitiveOptions {
        // Globally used
        const Math::Point3D center;
        Color color;
        std::shared_ptr<IMaterial> material;

        // Sphere
        double radius;
        // Plane
        const Math::Vector3D normal;
        // Triangle
        std::vector<Math::Point3D> vertices;
    };
}
