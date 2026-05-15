#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

Raytracer::ALight::ALight(Raytracer::LightOptions options) : _options(options)
{
}

Raytracer::Math::Vector3D Raytracer::ALight::getDirection(Raytracer::Math::Point3D) const
{
    return Math::Vector3D(0, 0, 0);
}

Raytracer::LightOptions Raytracer::ALight::getOptions() const
{
    return _options;
}

void Raytracer::ALight::modifyMultiplierForShadow(Math::Vector3D, Math::Vector3D, double &, double) const
{
}
