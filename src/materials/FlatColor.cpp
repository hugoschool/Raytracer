#include "materials/FlatColor.hpp"
#include "materials/AMaterial.hpp"
#include "materials/IMaterial.hpp"

Raytracer::FlatColor::FlatColor(Raytracer::MaterialOptions options) : AMaterial(options)
{
    _options.properties.reflexion = 0.1;
}

extern "C" Raytracer::IMaterial *materialEntrypoint(Raytracer::MaterialOptions options)
{
    return new Raytracer::FlatColor(options);
}

