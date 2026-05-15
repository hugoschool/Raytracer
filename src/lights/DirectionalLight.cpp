#include "lights/DirectionalLight.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

Raytracer::DirectionalLight::DirectionalLight(Raytracer::LightOptions options) : ALight(options)
{
}

Raytracer::Math::Vector3D Raytracer::DirectionalLight::getDirection(Raytracer::Math::Point3D) const
{
    return _options.direction;
}

extern "C" Raytracer::DirectionalLight *lightEntrypoint(Raytracer::LightOptions options)
{
    return new Raytracer::DirectionalLight(options);
}
