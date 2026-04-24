#include "lights/ALight.hpp"
#include "lights/LightOptions.hpp"

Raytracer::ALight::ALight(Raytracer::LightOptions options) : _options(options)
{
}

Raytracer::LightOptions Raytracer::ALight::getOptions() const
{
    return _options;
}
