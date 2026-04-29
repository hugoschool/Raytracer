#pragma once

#include "DLLoader.hpp"
#include "lights/ILight.hpp"
#include "lights/LightOptions.hpp"
#include "primitives/IPrimitive.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <unordered_map>
#include <map>
#include <memory>
#include <string>

namespace Raytracer {
    class Factory {
        public:
            Factory();
            ~Factory() = default;

            void registerAllPlugins();
            std::shared_ptr<IPrimitive> createPrimitive(const std::string name, PrimitiveOptions options) const;
            std::shared_ptr<ILight> createLight(const std::string name, LightOptions options) const;

        private:
            struct PluginConfig {
                // Category of the object (ex: "primitive")
                std::string category;

                // Name of the object (ex: "sphere")
                std::string name;

                bool operator==(const PluginConfig &other) const = default;
            };

            // For some unknown reason, I cannot use the "Custom specialization of std::hash"
            // So I have to resort to this trickery to make std::unordered_map work
            // See https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
            // and https://en.cppreference.com/cpp/utility/hash
            struct PluginConfigHash
            {
                std::size_t operator()(const PluginConfig& config) const noexcept
                {
                    std::size_t h1 = std::hash<std::string>{}(config.category);
                    std::size_t h2 = std::hash<std::string>{}(config.name);
                    return h1 ^ (h2 << 1);
                }
            };

            std::map<const std::string, std::shared_ptr<DLLoader>> _loaders;
            std::unordered_map<PluginConfig, std::function<IPrimitive *(PrimitiveOptions)>, PluginConfigHash> _primitives;
            std::unordered_map<PluginConfig, std::function<ILight *(LightOptions)>, PluginConfigHash> _lights;
    };
}
