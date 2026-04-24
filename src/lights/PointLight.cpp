#include "lights/PointLight.hpp"
#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

Raytracer::PointLight::PointLight(Raytracer::LightOptions options) : ALight(options)
{
}

extern "C" Raytracer::PointLight *lightEntrypoint(Raytracer::LightOptions options)
{
    return new Raytracer::PointLight(options);
}
