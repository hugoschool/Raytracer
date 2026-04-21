#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Camera.hpp"
#include "Ray.hpp"

Raytracer::Camera::Camera() : origin(0, 0, 0), screen()
{
}

Raytracer::Camera::Camera(const Math::Point3D origin, const Math::Rectangle3D screen) :
    origin(origin), screen(screen)
{
}


Raytracer::Ray Raytracer::Camera::ray(double u, double v)
{
    Math::Point3D point = screen.pointAt(u, v);
    Math::Vector3D direction = point - origin;

    return Raytracer::Ray(origin, direction);
}
