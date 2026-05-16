#include "transforms/Translate.hpp"
#include "transforms/ATransform.hpp"
#include "transforms/TransformOptions.hpp"

Raytracer::Translate::Translate(Raytracer::TransformOptions options) : ATransform(options)
{
}

void Raytracer::Translate::transformPrimitive(Raytracer::PrimitiveOptions &options)
{
    _options.ptr->transformPrimitive(options);

    options.center = options.center + _options.translate;
}

extern "C" Raytracer::ITransform *transformEntrypoint(Raytracer::TransformOptions options)
{
    return new Raytracer::Translate(options);
}
