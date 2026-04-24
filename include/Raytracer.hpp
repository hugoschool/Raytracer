#pragma once

#include "Camera.hpp"
#include "lights/ILight.hpp"
#include "DLLoader.hpp"
#include "primitives/IPrimitive.hpp"
#include <libconfig.h++>
#include <map>
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

            std::map<const std::string, std::shared_ptr<DLLoader<IPrimitive>>> _primitiveLoaders;
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<std::shared_ptr<ILight>> _lights;
    };
}
