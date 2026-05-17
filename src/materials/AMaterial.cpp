#include "materials/AMaterial.hpp"
#include "Color.hpp"
#include "Math/Point3D.hpp"
#include "materials/MaterialOptions.hpp"

Raytracer::AMaterial::AMaterial(Raytracer::MaterialOptions options) : _options(options)
{
}

Raytracer::MaterialOptions Raytracer::AMaterial::getOptions() const
{
    return _options;
}

Raytracer::Color Raytracer::AMaterial::applyMaterial(Raytracer::Color color, Math::Point3D) const 
{
    return color;
}