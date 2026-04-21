/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Matrix3x3.hpp
*/

#pragma once
#include "Math/Matrix3x1.hpp"
#include "Vector3D.hpp"
#include <array>
#include <cstddef>

namespace Raytracer {
    namespace Math {
        class Matrix3x3 {
            public:
                Matrix3x3();
                Matrix3x3(double, double, double, double, double, double, double, double, double);
                Matrix3x3(std::array<std::array<double, 3>, 3> &);
                Raytracer::Math::Matrix3x1 operator*(Matrix3x1 &other);

                ~Matrix3x3() = default;
                double get(size_t, size_t) const;
            private:
                std::array<std::array<double, 3>, 3> _matrix;
        };
    }
}
