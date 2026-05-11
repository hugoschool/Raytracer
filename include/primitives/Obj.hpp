#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include "primitives/Triangle.hpp"
#include <vector>

namespace Raytracer {
    class Obj : public APrimitive {
        public:
            Obj(PrimitiveOptions options);
            ~Obj() = default;

            HitInfo hits(Ray &ray) override;
            Math::Vector3D getNormal(const Math::Point3D) const override;
        private:
            std::vector<Math::Point3D> vertexs;
            std::vector<Triangle> triangles;
    };
}
