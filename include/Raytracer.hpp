#pragma once

#include "Camera.hpp"
#include "Config.hpp"
#include "Math/Point3D.hpp"
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
        private:
            const std::string _sceneFile;
            Config _config;
            Camera _camera;
            double random(double min, double max);
            Pixel hitIlluminance(std::shared_ptr<IPrimitive> &s, HitInfo &hit);
            Pixel handleHit(std::shared_ptr<IPrimitive> &s, HitInfo &hit, size_t left_occlusion, Ray &r, bool isAmbiant);
            Pixel mainHandleHit(Ray &r, size_t left_occlusion, bool isAmbiant);
            std::map<std::tuple<double, double, double>, std::pair<Pixel, size_t>>_colorCache;
            std::vector<Pixel> _pixels;
            std::shared_ptr<IPrimitive> _ignored_object;
            std::vector<std::shared_ptr<IPrimitive>> _primitives;
            std::vector<std::shared_ptr<ILight>> _lights;
            bool _toggleAmbiantOcclusion;
    };
}
