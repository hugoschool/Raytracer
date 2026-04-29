#pragma once

#include "Camera.hpp"
#include "Factory.hpp"
#include "lights/ILight.hpp"
#include "primitives/IPrimitive.hpp"
#include <functional>
#include <libconfig.h++>
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

            Factory _factory;

            Color parseColor(const libconfig::Setting &setting) const;
            PrimitiveOptions parsePrimitiveOptions(const libconfig::Setting &setting) const;
            LightOptions parseLightOptions(const libconfig::Setting &setting) const;
            MaterialOptions parseMaterialOptions(const libconfig::Setting &setting) const;
            std::shared_ptr<IMaterial> parseMaterial(const libconfig::Setting &setting) const;
    };
}
