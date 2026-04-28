#include "Config.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Exception.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
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

    PlaneAxis axis = PlaneAxis::None;
    if (!axisStr.empty()) {
        if (axisStr == "X" || axisStr == "x")
            axis = PlaneAxis::X;
        else if (axisStr == "Y" || axisStr == "y")
            axis = PlaneAxis::Y;
        else if (axisStr == "Z" || axisStr == "z")
            axis = PlaneAxis::Z;
        else
            throw Raytracer::Exception("Wrong plane direction");
    }

    Color color = parseColor(setting);

    return {
        .center = Math::Point3D(x, y, z),
        .color = color,
        .radius = static_cast<double>(r),
        .axis = axis,
        .position = position,
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
