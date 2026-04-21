/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Matrix.hpp
*/

#pragma once
#include "Vector3D.hpp"
#include <array>

namespace Raytracer {
    namespace Math {
        class Matrix3x3 {
            public:
                Matrix3x3();
                Matrix3x3(double, double, double, double, double, double, double, double, double);
                Matrix3x3(std::array<std::array<double, 3>, 3> &);

                Matrix3x3(Vector3D &);
                ~Matrix3x3() = default;
                Matrix3x3 rotateX(double angle);
                Matrix3x3 rotateY(double angle);
                Matrix3x3 rotateZ(double angle);
                Matrix3x3 operator*(Matrix3x3 &);
            private:
                std::array<std::array<double, 3>, 3> _matrix;
        };
    }
}
