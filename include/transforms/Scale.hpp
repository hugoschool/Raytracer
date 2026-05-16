#pragma once

#include "primitives/PrimitiveOptions.hpp"
#include "transforms/ATransform.hpp"
#include "transforms/TransformOptions.hpp"

namespace Raytracer {
    class Scale : public ATransform {
        public:
            Scale() = delete;
            Scale(TransformOptions options);
            ~Scale() = default;

            void transform(PrimitiveOptions &) override;

        private:
            void scaleTriangle(std::vector<Math::Point3D> &vertices);
    };
}
