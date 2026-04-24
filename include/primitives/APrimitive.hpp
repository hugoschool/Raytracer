#pragma once

#include "primitives/IPrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"

namespace Raytracer {
    class APrimitive : public IPrimitive {
        public:
            APrimitive() = delete;
            APrimitive(PrimitiveOptions options);
            ~APrimitive() = default;

            PrimitiveOptions getOptions() const override;

        protected:
            PrimitiveOptions _options;
    };
}
