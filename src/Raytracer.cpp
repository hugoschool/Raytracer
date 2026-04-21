#include "Raytracer.hpp"
#include <iostream>

// To be removed:
#include "Math/Point3D.hpp"
#include "primitives/Sphere.hpp"

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(), _width(), _height()
{
    _config.readFile(_sceneFile);
    const libconfig::Setting &root = _config.getRoot();

    try {
        const libconfig::Setting &camera = root["camera"];

        int x = 0;
        int y = 0;
        int z = 0;

        if (!(
            camera["position"].lookupValue("x", x) &&
            camera["position"].lookupValue("y", y) &&
            camera["position"].lookupValue("z", z) &&
            camera["resolution"].lookupValue("width", _width) &&
            camera["resolution"].lookupValue("height", _height)
        )) {
            throw std::exception();
        }

        _camera = Camera(
            Math::Point3D(x, y, z),
            Math::Rectangle3D(_width, _height)
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

            _primitives.push_back({Math::Point3D(x, y, z), static_cast<double>(r)});
        }
    } catch (const std::exception &e) {
        std::cerr << "Wrong primitives configuration" << std::endl;
        throw e;
    }
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

            for (Sphere &s : _primitives) {
                if (s.hits(r)) {
                    std::cout << "255 0 0" << std::endl;
                } else {
                    std::cout << "0 0 255" << std::endl;
                }
            }
        }
    }
}
