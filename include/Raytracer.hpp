#pragma once

#include "Camera.hpp"
#include "lights/Light.hpp"
#include "primitives/Sphere.hpp"
#include <libconfig.h++>
#include <string>
#include <vector>

namespace Raytracer {
    class Raytracer {
        public:
            Raytracer() = delete;
            Raytracer(const std::string sceneFile);
            ~Raytracer() = default;

            void exportPPM();
        private:
            const std::string _sceneFile;
            libconfig::Config _config;

            Camera _camera;
            unsigned int _width;
            unsigned int _height;
            void handleHit(Sphere &s, HitInfo &hit, Color &color);

            // TODO: important, replace with the interface
            std::vector<Sphere> _primitives;
            std::vector<Light> _lights;
    };
}
