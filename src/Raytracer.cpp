#include "Color.hpp"
#include "Raytracer.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <libconfig.h++>

// To be removed:
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "lights/Light.hpp"
#include "primitives/Sphere.hpp"

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(), _width(), _height(), _primitives(), _lights()
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

    // TODO: once again, remove hardcode here
    try {
        const libconfig::Setting &pointLights = root["lights"]["point"];
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

            _lights.push_back({Math::Point3D(x, y, z)});
        }
    } catch (const std::exception &e) {
        std::cerr << "Wrong light configuration" << std::endl;
        throw e;
    }
}


void Raytracer::Raytracer::handleHit(Sphere &s, HitInfo &hit, Color &color)
{
    double multiplier = 0.0;
    color = hit.getColor();
    for (Light &light: _lights) {
        Math::Vector3D light_Vector = light.getPos() - hit.getHitPos();
        Math::Vector3D normal = s.getNormal(hit.getHitPos());
        double tmpMultiplier = light_Vector.cosine(normal);
        if (tmpMultiplier <= 0)
            continue;
        Ray lightToHit(light.getPos(), light_Vector);
        for (Sphere &tmpSphere: _primitives) {
            if (tmpSphere.center == s.center && s.radius == tmpSphere.radius)
                continue;
            HitInfo tmpHitInfo = tmpSphere.hits(lightToHit);
            if (!tmpHitInfo.hasHit())
                continue;
            // on calcule la norme des deux vecteurs ainsi que le produit scalaire pour voir si le nouvel objet obstruct la lumière
            Math::Vector3D lightToNewObject = light.getPos() - tmpHitInfo.getHitPos();
            if (lightToNewObject.length() > light_Vector.length())
                continue;
            if (lightToNewObject.dot(light_Vector) > 0)
                continue;
            tmpMultiplier = 0.0;
            break;
        }
        multiplier += tmpMultiplier;
    }
    multiplier = std::min(1.0, multiplier);
    color = color * multiplier;
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
                    hasHit = true;
                    this->handleHit(s, hit, color);
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
