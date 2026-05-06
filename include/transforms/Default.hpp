#pragma once

#include "transforms/ATransform.hpp"
#include "transforms/TransformOptions.hpp"

namespace Raytracer {
    class Default : public ATransform {
        public:
            Default() = delete;
            Default(TransformOptions);
            ~Default() = default;
    };
}
