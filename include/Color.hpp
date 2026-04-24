#pragma once

namespace Raytracer {
    struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        Color operator*(double multiplier) {
            return Color(this->r * multiplier, this->g * multiplier, this->b * multiplier);
        }
    };
}
