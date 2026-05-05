#pragma once

#include "Camera.hpp"
#include "Config.hpp"
#include "Factory.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"
#include <libconfig.h++>
#include <memory>
#include <string>
#include <vector>

namespace Raytracer {
    struct Pixel {
        Color color;
        double multiplier;
    };

    class Raytracer {
        public:
            Raytracer() = delete;
            Raytracer(const std::string sceneFile);
            ~Raytracer() = default;

            void exportPPM();
            void render();
            void processImage(std::size_t yStart, std::size_t yEnd, std::size_t xStart, std::size_t xEnd);
            void launchGraphicalLibrary(std::string libraryName);

        private:
            const std::string _sceneFile;
            Factory _factory;
            Config _config;
            double _maxilluminance;
            Camera _camera;

            Pixel handleHit(std::shared_ptr<IPrimitive> &s, HitInfo &hit, Color &color);

            std::vector<std::vector<Pixel>> _pixels;
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<std::shared_ptr<ILight>> _lights;
    };
}
