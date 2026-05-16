#pragma once

#include "primitives/PrimitiveOptions.hpp"
#include "transforms/ATransform.hpp"
#include "transforms/TransformOptions.hpp"

namespace Raytracer {
    class Translate : public ATransform {
        public:
            Translate() = delete;
            Translate(TransformOptions options);
            ~Translate() = default;

            void transform(PrimitiveOptions &) override;
    };
}
