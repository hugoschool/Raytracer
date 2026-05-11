#pragma once

#include "Camera.hpp"
#include "Config.hpp"
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
            void processImage(std::size_t yStart, std::size_t yEnd, std::size_t xStart, std::size_t xEnd);
        private:
            const std::string _sceneFile;
            Config _config;
            Camera _camera;
            double random(double min, double max);
            Pixel hitIlluminance(std::shared_ptr<IPrimitive> &s, HitInfo &hit);
            Pixel handleHit(std::shared_ptr<IPrimitive> &s, HitInfo &hit, size_t left_occlusion, Ray &r, bool isAmbiant, std::shared_ptr<IPrimitive> ignoredObj);
            Pixel mainHandleHit(Ray &r, size_t left_occlusion, bool isAmbiant, std::shared_ptr<IPrimitive> ignoredObj);
            std::map<std::tuple<double, double, double>, std::pair<Pixel, size_t>> _colorCache;
            std::vector<std::vector<Pixel>> _pixels;
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<std::shared_ptr<ILight>> _lights;
            bool _toggleAmbiantOcclusion;
    };
}
