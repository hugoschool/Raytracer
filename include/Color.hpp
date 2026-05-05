#pragma once

#include "Math/Vector3D.hpp"
namespace Raytracer {
    struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        Color operator*(double multiplier) {
            return Color(this->r * multiplier, this->g * multiplier, this->b * multiplier);
        }
        Color operator*(const Color &other) {
            return Color(this->r * other.r, this->g * other.g, this->b * other.b);
        }
    };
}
