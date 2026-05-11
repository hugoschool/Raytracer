#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include "primitives/Triangle.hpp"
#include <string>
#include <utility>
#include <vector>

namespace Raytracer {
    class Obj : public APrimitive {
        public:
            Obj(PrimitiveOptions options);
            ~Obj() = default;

            HitInfo hits(Ray &ray) override;
            Math::Vector3D getNormal(const Math::Point3D) const override;
        private:
            std::vector<Math::Point3D> _vertices;
            std::vector<Triangle> _triangles;
            std::vector<std::pair<Math::Point3D, Math::Vector3D>> _pointToNormal;

            Math::Point3D lineToVertex(std::string line, PrimitiveOptions options);
            Triangle lineToTriangle(std::string line, PrimitiveOptions options);
    };
}
