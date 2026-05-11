#include "transforms/Default.hpp"
#include "transforms/ATransform.hpp"
#include "transforms/ITransform.hpp"
#include "transforms/TransformOptions.hpp"

Raytracer::Default::Default(TransformOptions options) : ATransform(options)
{
}

extern "C" Raytracer::ITransform *transformEntrypoint(Raytracer::TransformOptions options)
{
    return new Raytracer::Default(options);
}
