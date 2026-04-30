#include "Config.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Exception.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <array>
#include <exception>
#include <iostream>
#include <libconfig.h++>
#include <memory>

Raytracer::Config::Config(const std::string fileName) : _fileName(fileName), _config(), _factory()
{
    // Using as c_str for compilation on previous libconfig++
    _config.readFile(_fileName.c_str());
    _root = _config.getRoot();
}

Raytracer::Camera Raytracer::Config::parseCamera() const
{
    try {
        const libconfig::Setting &camera = _root->get()["camera"];

        int x = 0;
        int y = 0;
        int z = 0;
        unsigned int width;
        unsigned int height;
        double fov = 0.0;

        if (!(
            camera["position"].lookupValue("x", x) &&
            camera["position"].lookupValue("y", y) &&
            camera["position"].lookupValue("z", z) &&
            camera["resolution"].lookupValue("width", width) &&
            camera["resolution"].lookupValue("height", height) &&
            camera.lookupValue("fieldOfView", fov)
        )) {
            throw Exception("Invalid camera parameter");
        }

        Math::Point3D cameraOrigin(x, y, z);

        return Camera(
            cameraOrigin,
            Math::Rectangle3D(width, height, fov, cameraOrigin),
            width,
            height
        );
    } catch (const std::exception &e) {
        throw Raytracer::Exception("Wrong or missing camera parameter");
    }
}

Raytracer::Color Raytracer::Config::parseColor(const libconfig::Setting &setting) const
{
    unsigned int colorR;
    unsigned int colorG;
    unsigned int colorB;

    if (!(
        setting["color"].lookupValue("r", colorR) &&
        setting["color"].lookupValue("g", colorG) &&
        setting["color"].lookupValue("b", colorB)
    )) {
        throw Exception("Invalid color parameter");
    }

    if (colorR > 255 || colorG > 255 || colorB > 255)
        throw Exception("Color parameter exceeds 255");

    return {
        .r = static_cast<unsigned char>(colorR),
        .g = static_cast<unsigned char>(colorG),
        .b = static_cast<unsigned char>(colorB),
    };
}

std::array<std::array<long long, 3>, 3> Raytracer::Config::parseTriangle(const libconfig::Setting &setting) const
{
    std::array<std::string, 3> vertices_name = {"a", "b", "c"};
    std::array<std::array<long long, 3>, 3> vertices;
    for (size_t i = 0; i < 3; i++) {
        std::array<long long, 3> tmpArray;
        if (!(
            setting[vertices_name[i]].lookupValue("x", tmpArray[0]) &&
            setting[vertices_name[i]].lookupValue("y", tmpArray[1]) &&
            setting[vertices_name[i]].lookupValue("z", tmpArray[2])
        ))
            return vertices;
        vertices[i] = tmpArray;
    }
    return vertices;
}

Raytracer::PrimitiveOptions Raytracer::Config::parsePrimitiveOptions(const libconfig::Setting &setting) const
{
    long long x = 0;
    long long y = 0;
    long long z = 0;
    long long r = 0;
    std::string axisStr;
    long long position;

    setting.lookupValue("x", x);
    setting.lookupValue("y", y);
    setting.lookupValue("z", z);
    setting.lookupValue("r", r);
    setting.lookupValue("axis", axisStr);
    setting.lookupValue("position", position);
    Math::Vector3D normal;
    Math::Vector3D center = Math::Vector3D(x,y,z);

    if (!axisStr.empty()) {
        if (axisStr == "X" || axisStr == "x")
            normal = Math::Vector3D(-1,0,0);
        else if (axisStr == "Y" || axisStr == "y")
            normal = Math::Vector3D(0,-1,0);
        else if (axisStr == "Z" || axisStr == "z")
            normal = Math::Vector3D(0,0,-1);
        else
            throw Raytracer::Exception("Wrong plane direction");
        center = normal * position;
    }
    Color color = parseColor(setting);
    std::array<std::array<long long, 3>, 3> triangle;
    try {
        triangle = this->parseTriangle(setting);
    } catch(std::exception &e) {
        triangle[0] = {0,0,0};
        triangle[1] = {0,0,0};
        triangle[2] = {0,0,0};
    }
    return {
        .center = Math::Point3D(center.x, center.y, center.z),
        .color = color,
        .radius = static_cast<double>(r),
        .normal = normal,
        .a = Math::Point3D(triangle[0][0], triangle[0][1], triangle[0][2]),
        .b = Math::Point3D(triangle[1][0], triangle[1][1], triangle[1][2]),
        .c = Math::Point3D(triangle[2][0], triangle[2][1], triangle[2][2]),
    };
}

Raytracer::LightOptions Raytracer::Config::parseLightOptions(const libconfig::Setting &setting) const
{
    long long x = 0;
    long long y = 0;
    long long z = 0;

    setting.lookupValue("x", x);
    setting.lookupValue("y", y);
    setting.lookupValue("z", z);

    return {
        .position = Math::Point3D(x, y, z),
        .color = Color(),
    };
}

std::vector<std::shared_ptr<Raytracer::IPrimitive>> Raytracer::Config::parsePrimitives()
{
    std::vector<std::shared_ptr<Raytracer::IPrimitive>> primitives;

    try {
        for (const libconfig::Setting &primitiveCategory : _root->get()["primitives"]) {
            int count = primitiveCategory.getLength();

            for (int i = 0; i < count; i++) {
                const libconfig::Setting &primitive = primitiveCategory[i];

                const PrimitiveOptions options = parsePrimitiveOptions(primitive);

                primitives.push_back(
                    _factory.createPrimitive(primitiveCategory.getName(), options)
                );
            }
        }
        return primitives;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw Raytracer::Exception("Wrong primitives configuration");
    }
}

std::vector<std::shared_ptr<Raytracer::ILight>> Raytracer::Config::parseLights()
{
    std::vector<std::shared_ptr<Raytracer::ILight>> lights;

    try {
        for (const libconfig::Setting &lightCategory : _root->get()["lights"]) {
            int count = lightCategory.getLength();

            for (int i = 0; i < count; i++) {
                const libconfig::Setting &light = lightCategory[i];

                const LightOptions options = parseLightOptions(light);

                lights.push_back(
                    _factory.createLight(lightCategory.getName(), options)
                );
            }
        }
        return lights;
    } catch (const std::exception &e) {
        throw Raytracer::Exception("Wrong light configuration");
    }
}
