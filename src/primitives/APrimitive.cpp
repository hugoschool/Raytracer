#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"

Raytracer::APrimitive::APrimitive(Raytracer::PrimitiveOptions options) : _options(options)
{
}

Raytracer::PrimitiveOptions Raytracer::APrimitive::getOptions() const
{
    return _options;
}
