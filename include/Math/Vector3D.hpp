#pragma once

#include "Matrix3x1.hpp"
namespace Raytracer {
    namespace Math {
        class Matrix3x1;
        class Vector3D {
            public:
                Vector3D() = default;
                Vector3D(double x, double y, double z);
                Vector3D(const Matrix3x1 &matrix);

                ~Vector3D() = default;

                double x;
                double y;
                double z;

                double length();
                double dot(Vector3D &vector);



                Vector3D rotateX(double degree) const;
                Vector3D rotateY(double degree) const;
                Vector3D rotateZ(double degree) const;


                Vector3D operator+(const Vector3D &vector) const;
                Vector3D operator-(const Vector3D &vector) const;
                Vector3D operator*(const Vector3D &vector) const;
                Vector3D operator/(const Vector3D &vector) const;

                Vector3D operator*(const double nb) const;
                void operator*=(const double nb);

                void operator+=(const Vector3D &vector);
                void operator-=(const Vector3D &vector);
                void operator*=(const Vector3D &vector);
                void operator/=(const Vector3D &vector);
                Raytracer::Math::Vector3D operator=(const Raytracer::Math::Matrix3x1 &matrix);
        };
    }
}
