#include "primitives/IPrimitive.hpp"
#include "primitives/Sphere.hpp"

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Sphere(options);
}
