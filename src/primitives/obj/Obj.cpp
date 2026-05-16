#include "primitives/Obj.hpp"
#include "Exception.hpp"
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "primitives/Obj.hpp"
#include "Ray.hpp"
#include "primitives/APrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include "primitives/Triangle.hpp"
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

Raytracer::Obj::Obj(Raytracer::PrimitiveOptions options)
    : APrimitive(options), _vertices(), _triangles(), _pointToNormal(), _mutex()
{
    std::ifstream file(options.fileName);
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.starts_with("v ")) {
                try {
                    _vertices.push_back(lineToVertex(line, options));
                } catch (const std::exception &e) {
                }
            } else if (line.starts_with("f ")) {
                try {
                    _triangles.push_back(lineToTriangle(line, options));
                } catch (const std::exception &e) {
                }
            }
        }
        file.close();
    }
}

Raytracer::HitInfo Raytracer::Obj::hits(Raytracer::Ray &ray)
{
    std::optional<HitInfo> hit;
    Math::Vector3D normal;

    for (auto triangle: _triangles) {
        HitInfo temp = triangle.hits(ray);

        if (temp.hasHit() == true) {
            if (hit.has_value()) {
                if ((temp.getHitPos() - ray.origin).length() < (hit->getHitPos() - ray.origin).length()) {
                    hit = temp;
                    normal = triangle.getNormal(hit->getHitPos());
                }
            } else {
                hit = temp;
                normal = triangle.getNormal(hit->getHitPos());
            }
        }
    }

    if (hit.has_value()) {
        {
            const std::lock_guard<std::mutex> _lock(_mutex);

            _pointToNormal.push_back({hit->getHitPos(), normal});
        }
        return hit.value();
    } else {
        return HitInfo(false);
    }
}

Raytracer::Math::Vector3D Raytracer::Obj::getNormal(const Math::Point3D point) const
{
    for (auto pointNormal: _pointToNormal) {
        if (pointNormal.first == point) {
            return pointNormal.second;
        }
    }
    return Math::Vector3D(0, 0, 0);
}

Raytracer::Math::Point3D Raytracer::Obj::lineToVertex(std::string line, Raytracer::PrimitiveOptions options)
{
    std::stringstream stream(line);
    std::string str;
    double x, y, z;

    if (!getline(stream, str, ' ')) {
        throw Exception("invalid vertex");
    }

    if (!getline(stream, str, ' ')) {
        throw Exception("invalid vertex");
    }
    x = std::stod(str) * 10 + options.center.x;

    if (!getline(stream, str, ' ')) {
        throw Exception("invalid vertex");
    }
    y = std::stod(str) * 10 + options.center.y;

    if (!getline(stream, str, ' ')) {
        throw Exception("invalid vertex");
    }
    z = std::stod(str) * 10 + options.center.z;
    return Raytracer::Math::Point3D(x, y, z);
}

Raytracer::Triangle Raytracer::Obj::lineToTriangle(std::string line, Raytracer::PrimitiveOptions options)
{
    std::stringstream stream(line);
    std::string str;
    size_t index;
    PrimitiveOptions triangeOption = options;

    if (!getline(stream, str, ' ')) {
        throw Exception("invalid triangle");
    }

    if (!getline(stream, str, ' ')) {
        throw Exception("invalid triangle");
    }
    index = std::stoi(str);
    if (index < 1 || index > _vertices.size()) {
        throw Exception("invalid index");
    }
    triangeOption.vertices.push_back(_vertices[index - 1]);

    if (!getline(stream, str, ' ') && std::stoi(str) > 0) {
        throw Exception("invalid triangle");
    }
    index = std::stoi(str);
    if (index < 1 || index > _vertices.size()) {
        throw Exception("invalid index");
    }
    triangeOption.vertices.push_back(_vertices[index - 1]);

    if (!getline(stream, str, ' ') && std::stoi(str) > 0) {
        throw Exception("invalid triangle");
    }
    index = std::stoi(str);
    if (index < 1 || index > _vertices.size()) {
        throw Exception("invalid index");
    }
    triangeOption.vertices.push_back(_vertices[index - 1]);

    return Raytracer::Triangle(triangeOption);
}
