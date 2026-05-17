#include "materials/Transparent.hpp"
#include "materials/AMaterial.hpp"
#include "materials/IMaterial.hpp"

Raytracer::Transparent::Transparent(Raytracer::MaterialOptions options) : AMaterial(options)
{
    _options.properties.transparency = 0.6;
}

extern "C" Raytracer::IMaterial *materialEntrypoint(Raytracer::MaterialOptions options)
{
    return new Raytracer::Transparent(options);
}
