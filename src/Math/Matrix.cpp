#include "Math/Matrix.hpp"
#include "Math/Vector3D.hpp"
#include <array>

Raytracer::Math::Matrix3x3::Matrix3x3()
{
    this->_matrix[0] = {0, 0, 0};
    this->_matrix[1] = {0, 0, 0};
    this->_matrix[2] = {0, 0, 0};
}

Raytracer::Math::Matrix3x3::Matrix3x3(std::array<double, 9> arr)
{
    this->_matrix[0] = {arr[0], arr[1], arr[2]};
    this->_matrix[1] = {arr[3], arr[4], arr[5]};
    this->_matrix[2] = {arr[6], arr[7], arr[9]};
}

Raytracer::Math::Matrix3x3::Matrix3x3(Raytracer::Math::Vector3D vector)
{
    this->_matrix[0] = {vector.x, 0, 0};
    this->_matrix[1] = {0, vector.y, 0};
    this->_matrix[2] = {0, 0, vector.z};
}

Raytracer::Math::Matrix3x3::Matrix3x3(std::array<std::array<double, 3>, 3> arr) : _matrix(arr)
{
}

Raytracer::Math::Matrix3x3 Raytracer::Math::Matrix3x3::operator*(Matrix3x3 other)
{
    std::array<std::array<double, 3>, 3> result;

    for (std::size_t i = 0; i < 3; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }
    return Matrix3x3(result);
}
