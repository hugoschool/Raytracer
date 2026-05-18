#include "lights/AmbientLight.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

Raytracer::AmbientLight::AmbientLight(Raytracer::LightOptions options) : ALight(options)
{
}

Raytracer::Math::Vector3D Raytracer::AmbientLight::getDirection(Raytracer::Math::Point3D) const
{
    return Math::Vector3D(0, 0, 0);
}

void Raytracer::AmbientLight::modifyMultiplierForShadow(Raytracer::Math::Vector3D, Raytracer::Math::Vector3D, double &multiplier, double) const
{
    multiplier = _options.multiplier;
}

bool Raytracer::AmbientLight::skipHitDetection() const
{
    return true;
}

extern "C" Raytracer::AmbientLight *lightEntrypoint(Raytracer::LightOptions options)
{
    return new Raytracer::AmbientLight(options);
}
