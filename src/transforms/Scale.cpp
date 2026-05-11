#include "transforms/Scale.hpp"
#include "Math/Point3D.hpp"
#include "transforms/ATransform.hpp"
#include "transforms/TransformOptions.hpp"

Raytracer::Scale::Scale(Raytracer::TransformOptions options) : ATransform(options)
{
}

// https://stackoverflow.com/questions/8591991/algorithm-to-enlarge-scale-inflate-enbiggen-a-triangle
void Raytracer::Scale::scaleTriangle(std::vector<Math::Point3D> &vertices)
{
    if (vertices.size() != 3)
        return;

    Math::Point3D &first = vertices.at(0);
    Math::Point3D &second = vertices.at(1);
    Math::Point3D &third = vertices.at(2);

    Math::Point3D center(
        (first.x + second.x + third.x) / 3,
        (first.y + second.y + third.y) / 3,
        0
    );

    for (Math::Point3D &vertice : vertices) {
        vertice.x = center.x + (vertice.x - center.x) * _options.multiplier;
        vertice.y = center.y + (vertice.y - center.y) * _options.multiplier;
    }
}

void Raytracer::Scale::transformPrimitive(Raytracer::PrimitiveOptions &options)
{
    _options.ptr->transformPrimitive(options);

    if (_options.multiplier == 0)
        return;

    options.radius *= _options.multiplier;
    scaleTriangle(options.vertices);
}

extern "C" Raytracer::ITransform *transformEntrypoint(Raytracer::TransformOptions options)
{
    return new Raytracer::Scale(options);
}
