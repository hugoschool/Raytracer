#include "primitives/IPrimitive.hpp"
#include "primitives/Cube.hpp"

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Cube(options);
}
