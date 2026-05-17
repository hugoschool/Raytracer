#include "primitives/IPrimitive.hpp"
#include "primitives/Obj.hpp"

extern "C" Raytracer::IPrimitive *primitiveEntrypoint(Raytracer::PrimitiveOptions options)
{
    return new Raytracer::Obj(options);
}
