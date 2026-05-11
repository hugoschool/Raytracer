#include "primitives/IPrimitive.hpp"
#include "primitives/Triangle.hpp"

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Triangle(options);
}
