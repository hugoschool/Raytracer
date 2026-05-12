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

extern "C" Raytracer::PointLight *lightEntrypoint(Raytracer::LightOptions options)
{
    return new Raytracer::PointLight(options);
}
