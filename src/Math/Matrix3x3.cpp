#include "Math/Matrix3x3.hpp"
#include <array>
#include <cstddef>
#include <iostream>
#include <ostream>

Raytracer::Math::Matrix3x3::Matrix3x3()
{
    this->_matrix[0] = {0, 0, 0};
    this->_matrix[1] = {0, 0, 0};
    this->_matrix[2] = {0, 0, 0};
}

Raytracer::Math::Matrix3x3::Matrix3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i)
{
    this->_matrix[0] = {a, b, c};
    this->_matrix[1] = {d, e, f};
    this->_matrix[2] = {g, h, i};
}

Raytracer::Math::Matrix3x3::Matrix3x3(std::array<std::array<double, 3>, 3> &arr) : _matrix(arr)
{
}

Raytracer::Math::Matrix3x1 Raytracer::Math::Matrix3x3::operator*(Matrix3x1 &other)
{
    std::array<double, 3> result;

    for (std::size_t i = 0; i < 3; i++) {
        result[i] = 0;
        for (std::size_t j = 0; j < 3; j++) {
            result[i] += this->_matrix[i][j] * other.get(j);
        }
    }
    return Matrix3x1(result);
}

double Raytracer::Math::Matrix3x3::get(size_t y, size_t x)
{
    if (y >= this->_matrix.size() || x >= this->_matrix[y].size()) {
        std::cerr << "Out of bound reach on matrix" << std::endl;
        return 0;
    }
    return _matrix[y][x];
}