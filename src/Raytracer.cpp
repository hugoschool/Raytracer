#include "Raytracer.hpp"
#include <iostream>

// To be removed:
#include "primitives/Sphere.hpp"

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(), _camera()
{
    _config.readFile(_sceneFile);
}

void Raytracer::Raytracer::exportPPM()
{
    Sphere s(Math::Point3D(0, 0, -200), 120);

    std::size_t maxX = 400;
    std::size_t maxY = 400;

    std::cout << "P3" << std::endl;
    std::cout << maxX << " " << maxY << std::endl;
    std::cout << "255" << std::endl;

    for (std::size_t y = 0; y < maxY; y++) {
        for (std::size_t x = 0; x < maxX; x++) {
            double u = static_cast<double>(x) / maxX;
            double v = static_cast<double>(y) / maxY;
            Ray r = _camera.ray(u, v);

            if (s.hits(r)) {
                std::cout << "255 0 0" << std::endl;
            } else {
                std::cout << "0 0 255" << std::endl;
            }
        }
    }
}
