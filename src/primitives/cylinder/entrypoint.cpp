#include "primitives/IPrimitive.hpp"
#include "primitives/Cylinder.hpp"

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Cylinder(options);
}
