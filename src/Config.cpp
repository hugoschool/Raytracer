#include "Config.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Exception.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"
#include <libconfig.h++>
#include <memory>

Raytracer::Config::Config(const std::string fileName) : _fileName(fileName), _config(), _factory()
{
    _config.readFile(_fileName);
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

std::vector<std::shared_ptr<Raytracer::IPrimitive>> Raytracer::Config::parsePrimitives()
{
    std::vector<std::shared_ptr<Raytracer::IPrimitive>> primitives;

    try {
        const libconfig::Setting &spheres = _root->get()["primitives"]["spheres"];
        int count = spheres.getLength();

        for (int i = 0; i < count; i++) {
            const libconfig::Setting &sphere = spheres[i];
            long long x = 0;
            long long y = 0;
            long long z = 0;
            long long r = 0;

            if (!(
                sphere.lookupValue("x", x) &&
                sphere.lookupValue("y", y) &&
                sphere.lookupValue("z", z) &&
                sphere.lookupValue("r", r)
            )) {
                throw Exception("Invalid sphere parameter");
            }

            Color color = parseColor(sphere);

            PrimitiveOptions options = {
                Math::Point3D(x, y, z),
                color,
                static_cast<double>(r)
            };

            primitives.push_back(
                _factory.createPrimitive("sphere", options)
            );
        }

        return primitives;
    } catch (const std::exception &e) {
        throw Raytracer::Exception("Wrong primitives configuration");
    }
}

std::vector<std::shared_ptr<Raytracer::ILight>> Raytracer::Config::parseLights()
{
    std::vector<std::shared_ptr<Raytracer::ILight>> lights;

    // TODO: once again, remove hardcode here
    try {
        const libconfig::Setting &pointLights = _root->get()["lights"]["point"];
        int count = pointLights.getLength();

        for (int i = 0; i < count; i++) {
            const libconfig::Setting &light = pointLights[i];
            long long x = 0;
            long long y = 0;
            long long z = 0;

            if (!(
                light.lookupValue("x", x) &&
                light.lookupValue("y", y) &&
                light.lookupValue("z", z)
            )) {
                throw std::exception();
            }

            LightOptions options = {
                .position = Math::Point3D(x, y, z),
                .color = Color(),
            };

            lights.push_back(
                _factory.createLight("point", options)
            );
        }
        return lights;
    } catch (const std::exception &e) {
        throw Raytracer::Exception("Wrong light configuration");
    }
}
