#pragma once

#include "Camera.hpp"
#include "Config.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"
#include <libconfig.h++>
#include <memory>
#include <string>
#include <tuple>
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
        private:
            const std::string _sceneFile;
            Config _config;
            double _maxilluminance;
            Camera _camera;
            Color hitIlluminance(std::shared_ptr<IPrimitive> &s, HitInfo &hit);
            Color handleHitOther(std::shared_ptr<IPrimitive> &s, HitInfo &hit, size_t left_occlusion, Ray &r);
            Color mainHandleHit(Ray &r, size_t left_occlusion);
            std::map<std::tuple<double, double, double>, Pixel>_colorCache;
            std::vector<Color> _pixels;
            std::shared_ptr<IPrimitive> _ignored_object;
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<std::shared_ptr<ILight>> _lights;
    };
}
