#pragma once

#include "Camera.hpp"
#include "DLLoader.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"
#include <functional>
#include <libconfig.h++>
#include <map>
#include <memory>
#include <optional>
#include <string>

namespace Raytracer {
    class Config {
        public:
            Config() = delete;
            Config(const std::string fileName);
            ~Config() = default;

            Camera parseCamera() const;
            std::vector<std::shared_ptr<IPrimitive>> parsePrimitives();
            std::vector<std::shared_ptr<ILight>> parseLights();

        private:
            const std::string _fileName;

            libconfig::Config _config;
            std::optional<std::reference_wrapper<libconfig::Setting>> _root;

            // TODO: move to factory
            std::map<const std::string, std::shared_ptr<DLLoader>> _loaders;

            Color parseColor(const libconfig::Setting &setting) const;
    };
}
