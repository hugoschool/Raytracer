#include "Config.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Exception.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "lights/ILight.hpp"
#include "materials/IMaterial.hpp"
#include "materials/MaterialOptions.hpp"
#include "primitives/IPrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include "transforms/ITransform.hpp"
#include "transforms/TransformOptions.hpp"
#include <exception>
#include <iostream>
#include <libconfig.h++>
#include <memory>
#include <unordered_map>
#include <vector>

Raytracer::Config::Config(const std::string fileName) : _fileName(fileName), _config(), _factory(),
    _otherConfigs()
{
    // Using as c_str for compilation on previous libconfig++
    _config.readFile(_fileName.c_str());
    _root = _config.getRoot();
}

void Raytracer::Config::walkIncludes(std::unordered_map<std::string, std::optional<std::shared_ptr<Config>>> &includes)
{
    if (!_root->get().exists("scene"))
        return;

    const libconfig::Setting &setting = _root->get()["scene"];

    if (!setting.exists("includes"))
        return;

    for (const libconfig::Setting &include : setting["includes"]) {
        std::string name;

        if (!include.lookupValue("name", name))
            continue;

        if (includes.contains(name))
            continue;

        std::shared_ptr<Config> config = std::make_shared<Config>(name);
        includes.insert({name, config});
        config->walkIncludes(includes);
    }
}

void Raytracer::Config::parseIncludes()
{
    // This map prevents infinite loop / recursive includes
    std::unordered_map<std::string, std::optional<std::shared_ptr<Config>>> includes;

    includes.insert({_fileName, std::nullopt});
    walkIncludes(includes);
    for (auto &[_, value] : includes) {
        if (!value.has_value())
            continue;
        _otherConfigs.push_back(std::move(value.value()));
    }
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
            Screen(width, height, fov, cameraOrigin),
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

std::vector<Raytracer::Math::Point3D> Raytracer::Config::parseVertices(const libconfig::Setting &initialSetting) const
{
    std::vector<Math::Point3D> vertices;

    if (!initialSetting.exists("vertices"))
        return vertices;

    const libconfig::Setting &setting = initialSetting["vertices"];

    for (const libconfig::Setting &vertice : setting) {
        long long x = 0;
        long long y = 0;
        long long z = 0;

        vertice.lookupValue("x", x);
        vertice.lookupValue("y", y);
        vertice.lookupValue("z", z);

        vertices.push_back({
            static_cast<double>(x),
            static_cast<double>(y),
            static_cast<double>(z)
        });
    }
    return vertices;
}

Raytracer::MaterialOptions Raytracer::Config::parseMaterialOptions(const libconfig::Setting &) const
{
    return {
        .color = Color(),
        .properties = {
            .transparency = 0.0,
            .reflexion = 0.0,
            .refraction = 0.0
        }
    };
}

std::shared_ptr<Raytracer::IMaterial> Raytracer::Config::parseMaterial(const libconfig::Setting &initialSetting) const
{
    if (!initialSetting.exists("material")) {
        // If no option specified, use flat color material.
        MaterialOptions options = {
            .color = Color(0, 0, 0),
            .properties = {
                .transparency = 0.0,
                .reflexion = 0.0,
                .refraction = 0.0
            },
        };
        return _factory.createMaterial("flatcolor", options);
    }

    const libconfig::Setting &setting = initialSetting["material"];
    std::string name;

    setting.lookupValue("name", name);

    return _factory.createMaterial(name, {});
}

Raytracer::Math::Vector3D Raytracer::Config::parseCylinderAxis(const libconfig::Setting &setting) const
{
    long long x;
    long long y;
    long long z;

    if (setting["cylinderAxis"].lookupValue("x", x) == false) {
        x = 0;
    }
    if (setting["cylinderAxis"].lookupValue("y", y) == false) {
        y = 0;
    }
    if (setting["cylinderAxis"].lookupValue("z", z) == false) {
        z = 0;
    }
    return Math::Vector3D(static_cast<double>(x), static_cast<double>(y), static_cast<double>(z));
}

std::shared_ptr<Raytracer::ITransform> Raytracer::Config::parseTransform(
    const libconfig::Setting &setting,
    std::shared_ptr<ITransform> ptr
) const
{
    if (!setting.exists("transforms"))
        return ptr;

    for (const libconfig::Setting &transform : setting["transforms"]) {
        std::string type;
        double multiplier = 0;

        if (!transform.lookupValue("type", type))
            throw Exception("Invalid transform type");
        transform.lookupValue("multiplier", multiplier);

        TransformOptions options = {
            .ptr = ptr,
            .multiplier = multiplier,
        };
        ptr = _factory.createTransform(type, options);
    }
    return ptr;
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

    TransformOptions transformOptions;
    std::shared_ptr<ITransform> transform = _factory.createTransform("default", transformOptions);
    transform = parseTransform(setting, transform);

    Math::Vector3D normal;
    Math::Vector3D center = Math::Vector3D(x,y,z);

    Math::Vector3D cylinderAxis(0, 0, 0);
    if (setting.exists("cylinderAxis")) {
        cylinderAxis = parseCylinderAxis(setting);
    }

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

    double length = 0;

    setting.lookupValue("length", length);

    Color color = parseColor(setting);

    std::vector<Math::Point3D> vertices = parseVertices(setting);

    Raytracer::PrimitiveOptions options{
        .center = Math::Point3D(center.x, center.y, center.z),
        .color = color,
        .material = parseMaterial(setting),
        .transform = transform,
        .radius = static_cast<double>(r),
        .normal = normal,
        .vertices = vertices,
        .cylinderAxis = cylinderAxis,
        .length = length
    };

    options.transform->transformPrimitive(options);
    return options;
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
        .color = Color(255,255,255),
    };
}

std::vector<std::shared_ptr<Raytracer::IPrimitive>> Raytracer::Config::parsePrimitives()
{
    std::vector<std::shared_ptr<Raytracer::IPrimitive>> primitives;

    for (std::shared_ptr<Config> &config : _otherConfigs) {
        std::vector configPrimitives = config->parsePrimitives();
        primitives.insert(primitives.end(), configPrimitives.begin(), configPrimitives.end());
    }
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

    for (std::shared_ptr<Config> &config : _otherConfigs) {
        std::vector configLights = config->parseLights();
        lights.insert(lights.end(), configLights.begin(), configLights.end());
    }
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
