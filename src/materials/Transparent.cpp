#include "materials/Metallic.hpp"
#include "materials/AMaterial.hpp"
#include "materials/IMaterial.hpp"

Raytracer::Metallic::Metallic(Raytracer::MaterialOptions options) : AMaterial(options)
{
    _options.properties.transparency = 0.6;   
}

extern "C" Raytracer::IMaterial *materialEntrypoint(Raytracer::MaterialOptions options)
{
    return new Raytracer::Metallic(options);
}
