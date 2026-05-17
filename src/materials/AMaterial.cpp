#include "materials/AMaterial.hpp"
#include "materials/MaterialOptions.hpp"

Raytracer::AMaterial::AMaterial(Raytracer::MaterialOptions options) : _options(options)
{
}

Raytracer::MaterialOptions Raytracer::AMaterial::getOptions() const
{
    return _options;
}
