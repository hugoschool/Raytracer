#pragma once

#include "Color.hpp"
#include "Math/Point3D.hpp"
namespace Raytracer {
    class Light {
        public:
            Light() = default;
            ~Light() = default;
            Light(Math::Point3D);
            Light(Math::Point3D, Color);
            Math::Point3D getPos();
            Color getColor();

        private:
            Math::Point3D _position;
            Color _color;
    };
}
