#pragma once

#include "Math/Vector3D.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include "transforms/ITransform.hpp"
#include "transforms/TransformOptions.hpp"

namespace Raytracer {
    class ATransform : public ITransform {
        public:
            ATransform() = delete;
            ATransform(TransformOptions options);
            ~ATransform() = default;

            void transform(Math::Vector3D &) override;
            void transform(Math::Point3D &) override;
            void transform(PrimitiveOptions &) override;

        protected:
            TransformOptions _options;
    };
}
