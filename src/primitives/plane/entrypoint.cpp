#include "primitives/IPrimitive.hpp"
#include "primitives/Plane.hpp"

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Plane(options);
}
