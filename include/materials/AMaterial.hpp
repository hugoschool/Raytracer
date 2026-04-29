#pragma once

#include "materials/IMaterial.hpp"
#include "materials/MaterialOptions.hpp"

namespace Raytracer {
    class AMaterial : public IMaterial {
        public:
            AMaterial() = delete;
            AMaterial(MaterialOptions options);
            ~AMaterial() = default;

            MaterialOptions getOptions() const override;

        private:
            MaterialOptions _options;
    };
}
