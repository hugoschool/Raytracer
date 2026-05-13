#pragma once

#include "Math/Point3D.hpp"
#include "Color.hpp"
#include "Math/Vector3D.hpp"
#include "transforms/ITransform.hpp"
#include <memory>
#include <vector>
#include "materials/IMaterial.hpp"
#include <memory>

namespace Raytracer {
    class ITransform;
    struct PrimitiveOptions {
        // Globally used
        const Math::Point3D center;
        Color color;
        std::shared_ptr<IMaterial> material;
        std::shared_ptr<ITransform> transform;

        // Sphere & Cylinder
        double radius;
        // Plane
        const Math::Vector3D normal;
        // Triangle
        std::vector<Math::Point3D> vertices;
        // Cylinder
        Math::Vector3D cylinderAxis;
        // Cube
        double length;
    };
}
