#pragma once

#include <libconfig.h++>
#include <string>

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
    };
}
