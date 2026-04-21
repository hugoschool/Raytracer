#pragma once

namespace Raytracer {
    namespace Math {
        class Vector3D {
            public:
                Vector3D() = default;
                Vector3D(double x, double y, double z);
                ~Vector3D() = default;

                double x;
                double y;
                double z;

                double length();
                double dot(Vector3D &vector);

                Vector3D operator+(const Vector3D &vector) const;
                Vector3D operator-(const Vector3D &vector) const;
                Vector3D operator*(const Vector3D &vector) const;
                Vector3D operator/(const Vector3D &vector) const;

                Vector3D operator*(const double nb) const;

                Vector3D rotateX(double degree) const;
                Vector3D rotateY(double degree) const;
                Vector3D rotateZ(double degree) const;

                void operator+=(const Vector3D &vector);
                void operator-=(const Vector3D &vector);
                void operator*=(const Vector3D &vector);
                void operator/=(const Vector3D &vector);

                // TODO: +=, -=, *=, / and /=
        };
    }
}
