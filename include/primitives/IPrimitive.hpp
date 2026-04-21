#pragma once

#include "Ray.hpp"

namespace Raytracer {
    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;

            bool hits(Raytracer::Ray &ray);
    };
}
