#include "materials/FlatColor.hpp"
#include "materials/AMaterial.hpp"
#include "materials/IMaterial.hpp"

Raytracer::FlatColor::FlatColor(Raytracer::MaterialOptions options) : AMaterial(options)
{
}

extern "C" Raytracer::IMaterial *materialEntrypoint(Raytracer::MaterialOptions options)
{
    return new Raytracer::FlatColor(options);
}

