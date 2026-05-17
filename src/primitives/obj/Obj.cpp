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
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <regex>
#include <string>
#include <vector>

Raytracer::Obj::Obj(Raytracer::PrimitiveOptions options)
    : APrimitive(options), _vertices(), _triangles(), _pointToNormal(), _mutex()
{
    std::ifstream file(options.fileName);
    std::string line;

    if (!file.is_open())
        throw Exception("Couldn't open " + _options.fileName);

    const std::string ignoreWhitespaceRegexPart = "(?:\\s+)";
    const std::string floatRegexPart = "([+-]?(?:[0-9]*[.])?[0-9]+)";
    const std::string numberRegexPart = "([+-]?[0-9]+)";
    std::regex vertexRegex(
        "v" + ignoreWhitespaceRegexPart +
        floatRegexPart + ignoreWhitespaceRegexPart +
        floatRegexPart + ignoreWhitespaceRegexPart +
        floatRegexPart);
    std::regex triangleRegex(
        "f" + ignoreWhitespaceRegexPart +
        numberRegexPart + ignoreWhitespaceRegexPart +
        numberRegexPart + ignoreWhitespaceRegexPart +
        numberRegexPart);

    while (getline(file, line)) {
        std::smatch matches;

        if (std::regex_match(line, matches, vertexRegex)) {
            try {
                _vertices.push_back(lineToVertex(matches, options));
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        if (std::regex_match(line, matches, triangleRegex)) {
            try {
                _triangles.push_back(lineToTriangle(matches, options));
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    file.close();
}

Raytracer::HitInfo Raytracer::Obj::hits(Raytracer::Ray &ray)
{
    std::optional<HitInfo> hit;
    Math::Vector3D normal;

    for (Triangle &triangle : _triangles) {
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
    {
        // The casting here is necessary as getNormal is a const function
        // But modifying a mutex is not const
        const std::lock_guard<std::mutex> _lock(const_cast<Raytracer::Obj *>(this)->_mutex);

        for (auto &pointNormal : _pointToNormal) {
            if (pointNormal.first == point) {
                return pointNormal.second;
            }
        }
    }
    return Math::Vector3D(0, 0, 0);
}

Raytracer::Math::Point3D Raytracer::Obj::lineToVertex(std::smatch &matches, Raytracer::PrimitiveOptions options)
{
    double x = std::stod(matches[1]) * 10 + options.center.x;
    double y = std::stod(matches[2]) * 10 + options.center.y;
    double z = std::stod(matches[3]) * 10 + options.center.z;

    return Raytracer::Math::Point3D(x, y, z);
}

Raytracer::Triangle Raytracer::Obj::lineToTriangle(std::smatch &matches, Raytracer::PrimitiveOptions options)
{
    size_t index;
    PrimitiveOptions triangleOption = options;

    index = std::stoi(matches[1]);
    if (index < 1 || index > _vertices.size()) {
        throw Exception("invalid index");
    }
    triangleOption.vertices.push_back(_vertices[index - 1]);

    index = std::stoi(matches[2]);
    if (index < 1 || index > _vertices.size()) {
        throw Exception("invalid index");
    }
    triangleOption.vertices.push_back(_vertices[index - 1]);

    index = std::stoi(matches[3]);
    if (index < 1 || index > _vertices.size()) {
        throw Exception("invalid index");
    }
    triangleOption.vertices.push_back(_vertices[index - 1]);

    return Raytracer::Triangle(triangleOption);
}
