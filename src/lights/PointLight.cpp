#include "lights/PointLight.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

Raytracer::PointLight::PointLight(Raytracer::LightOptions options) : ALight(options)
{
}

Raytracer::Math::Vector3D Raytracer::PointLight::getDirection(Raytracer::Math::Point3D origin) const
{
    return _options.position - origin;
}

void Raytracer::PointLight::modifyMultiplierForShadow(Math::Vector3D distance, Math::Vector3D lightDistance, double &multiplier, double) const
{
    if (lightDistance.length() < distance.length() && distance.dot(lightDistance) > 0) {
        multiplier = 0.0;
    }
}

Raytracer::Ray Raytracer::PointLight::getRay(Raytracer::Math::Vector3D &vec, Raytracer::HitInfo &) const
{
    return Ray(_options.position, vec);
}

extern "C" Raytracer::PointLight *lightEntrypoint(Raytracer::LightOptions options)
{
    return new Raytracer::PointLight(options);
}
