#include "transforms/ATransform.hpp"
#include "transforms/TransformOptions.hpp"

Raytracer::ATransform::ATransform(TransformOptions options) : _options(options)
{
}

void Raytracer::ATransform::transform(Raytracer::Math::Vector3D &)
{
}

void Raytracer::ATransform::transform(Raytracer::Math::Point3D &)
{
}

void Raytracer::ATransform::transform(Raytracer::PrimitiveOptions &)
{
}
