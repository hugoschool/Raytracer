#include "transforms/ATransform.hpp"
#include "transforms/TransformOptions.hpp"

Raytracer::ATransform::ATransform(TransformOptions options) : _options(options)
{
}

void Raytracer::ATransform::transformVector(Raytracer::Math::Vector3D &)
{
}

void Raytracer::ATransform::transformPoint(Raytracer::Math::Point3D &)
{
}
