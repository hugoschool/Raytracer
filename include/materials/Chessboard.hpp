#pragma once

#include "materials/AMaterial.hpp"
#include "materials/MaterialOptions.hpp"

namespace Raytracer {
    class Chessboard : public AMaterial {
        public:
            Chessboard() = delete;
            Chessboard(MaterialOptions options);
            Color applyMaterial(Color, Math::Point3D) const override;
            ~Chessboard() = default;
    };
}
