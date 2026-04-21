/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Matrix3x3.hpp
*/

#pragma once
#include "Vector3D.hpp"
#include <array>
#include <cstddef>

namespace Raytracer {
    namespace Math {
        class Matrix3x1 {
            public:
                Matrix3x1();
                Matrix3x1(double, double, double);
                Matrix3x1(std::array<double, 3> &);
                Matrix3x1(Vector3D &);

                ~Matrix3x1() = default;
                Matrix3x1 rotateX(double angle);
                Matrix3x1 rotateY(double angle);
                Matrix3x1 rotateZ(double angle);
                double get(size_t);
            private:
                std::array<double, 3> _matrix;
        };
    }
}
