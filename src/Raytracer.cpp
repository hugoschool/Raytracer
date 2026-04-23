#include "Color.hpp"
#include "Raytracer.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

// To be removed:
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "lights/Light.hpp"
#include "primitives/Sphere.hpp"

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(), _width(), _height(), _light(Math::Point3D(0,100,0))
{
    // TODO: all of this should probably be moved to its own class
    _config.readFile(_sceneFile);
    const libconfig::Setting &root = _config.getRoot();

    try {
        const libconfig::Setting &camera = root["camera"];

        int x = 0;
        int y = 0;
        int z = 0;
        double fov = 0.0;

        if (!(
            camera["position"].lookupValue("x", x) &&
            camera["position"].lookupValue("y", y) &&
            camera["position"].lookupValue("z", z) &&
            camera["resolution"].lookupValue("width", _width) &&
            camera["resolution"].lookupValue("height", _height) &&
            camera.lookupValue("fieldOfView", fov)
        )) {
            throw std::exception();
        }

        Math::Point3D cameraOrigin(x, y, z);

        _camera = Camera(
            cameraOrigin,
            Math::Rectangle3D(_width, _height, fov, cameraOrigin)
        );
    } catch (const std::exception &e) {
        std::cerr << "Wrong or missing camera parameter" << std::endl;
        throw e;
    }

    try {
        // This is only temporary, to be removed also
        const libconfig::Setting &spheres = root["primitives"]["spheres"];
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
                throw std::exception();
            }

            unsigned int colorR;
            unsigned int colorG;
            unsigned int colorB;
            Color color;

            if (!(
                sphere["color"].lookupValue("r", colorR) &&
                sphere["color"].lookupValue("g", colorG) &&
                sphere["color"].lookupValue("b", colorB)
            )) {
                throw std::exception();
            }

            // TODO: verify that color is < 255
            color = {
                .r = static_cast<unsigned char>(colorR),
                .g = static_cast<unsigned char>(colorG),
                .b = static_cast<unsigned char>(colorB),
            };

            _primitives.push_back({Math::Point3D(x, y, z), static_cast<double>(r), color});
        }
    } catch (const std::exception &e) {
        std::cerr << "Wrong primitives configuration" << std::endl;
        throw e;
    }
    // To be changed, this is only temporary as this is highly unefficient and only works for sphere collisions
    std::sort(_primitives.begin(), _primitives.end(), [](Sphere &a, Sphere &b)
    {
        return a.center.z > b.center.z;
    });
}


double Raytracer::Raytracer::lightLevel(Math::Vector3D &lightVector, Math::Vector3D &normalVector)
{
    double value = lightVector.dot(normalVector) / (lightVector.length() * normalVector.length());
    value = std::max(0.0, value);
    return value;
}

void Raytracer::Raytracer::handleHit(Sphere &s, HitInfo &hit, Color &color, bool &hasHit)
{
    hasHit = true;
    Math::Vector3D light_Vector = this->_light.getPos() - hit.getHitPos();
    for (Sphere &tmpSphere : _primitives) {
        if (s.center == tmpSphere.center && s.radius == tmpSphere.radius)
            continue;
    }
    Math::Vector3D normal = s.getNormal(hit.getHitPos());
    color = hit.getColor();
    double multiplier = this->lightLevel(light_Vector, normal);
    color.r *= multiplier;
    color.b *= multiplier;
    color.g *= multiplier;
}

void Raytracer::Raytracer::exportPPM()
{
    std::cout << "P3" << std::endl;
    std::cout << _width << " " << _height << std::endl;
    std::cout << "255" << std::endl;

    for (std::size_t y = 0; y < _height; y++) {
        for (std::size_t x = 0; x < _width; x++) {
            double u = static_cast<double>(x) / _width;
            double v = static_cast<double>(y) / _height;
            Ray r = _camera.ray(u, v);

            bool hasHit = false;
            Color color;
            for (Sphere &s : _primitives) {
                HitInfo hit = s.hits(r);
                if (hit.hasHit()) {
                    this->handleHit(s, hit, color, hasHit);
                    break;
                }
            }
            if (hasHit) {
                std::cout   << static_cast<unsigned int>(color.r) << " "
                            << static_cast<unsigned int>(color.g) << " "
                            << static_cast<unsigned int>(color.b) << std::endl;
            } else
                std::cout << "0 0 0" << std::endl;
        }
    }
}
