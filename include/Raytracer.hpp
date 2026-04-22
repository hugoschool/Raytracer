#pragma once

#include "Camera.hpp"
#include "Math/Vector3D.hpp"
#include "lights/Light.hpp"
#include "primitives/Sphere.hpp"
#include "primitives/IPrimitive.hpp"
#include <libconfig.h++>
#include <memory>
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
            void handleHit(std::shared_ptr<IPrimitive> &s, HitInfo &hit, Color &color);

            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<Light> _lights;
    };
}
