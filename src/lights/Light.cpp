#include "lights/Light.hpp"
#include "Color.hpp"
#include "Math/Point3D.hpp"

Raytracer::Light::Light(Raytracer::Math::Point3D pos) : _position(pos), _color()
{
}

Raytracer::Light::Light(Raytracer::Math::Point3D pos, Color color) : _position(pos), _color(color)
{
}

Raytracer::Color Raytracer::Light::getColor()
{
    return this->_color;
}

Raytracer::Math::Point3D Raytracer::Light::getPos()
{
    return this->_position;
}