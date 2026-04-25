#include "Factory.hpp"
#include "Utils.hpp"
#include "primitives/PrimitiveOptions.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>

Raytracer::Factory::Factory()
{
    registerAllPlugins();
}

void Raytracer::Factory::registerAllPlugins()
{
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(Utils::pluginsDir)) {
        const std::filesystem::path fsPath = entry.path();
        const std::string libraryPath = fsPath.string();
        const std::string libraryFilename = fsPath.filename();
        const std::string libraryOnlyFilename = fsPath.filename().replace_extension();

        char delim = '_';
        if (std::count(libraryOnlyFilename.begin(), libraryOnlyFilename.end(), delim) != 2) {
            std::cerr << "Incorrect plugin name: " << libraryOnlyFilename << ". Skipping over it." << std::endl;
            continue;
        }

        std::stringstream ss(libraryOnlyFilename);
        std::string token;
        PluginConfig config;

        // Ignore the raytracer bit
        std::getline(ss, token, delim);

        // Category name
        std::getline(ss, token, delim);
        config.category = std::string(token);

        // Object name
        std::getline(ss, token, delim);
        config.name = std::string(token);

        std::shared_ptr<DLLoader> loader = std::make_shared<DLLoader>(libraryPath);

        _loaders.insert({libraryPath, loader});

        if (loader->symbolExists(std::string(Utils::primitiveEntrypoint))) {
            _primitives.insert({
                config,
                loader->getSymbol<IPrimitive, PrimitiveOptions>(std::string(Utils::primitiveEntrypoint))
            });
        } else if (loader->symbolExists(std::string(Utils::lightEntrypoint))) {
            _lights.insert({
                config,
                loader->getSymbol<ILight, LightOptions>(std::string(Utils::lightEntrypoint))
            });
        }
    }
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::Factory::createPrimitive(const std::string name, PrimitiveOptions options)
{
    try {
        std::function function = _primitives.at({
            .category = std::string("primitive"),
            .name = name
        });

        return DLLoader::turnFunctionIntoInstance(function, options);
    } catch (const std::exception &e) {
        throw Exception("Couldn't find " + name);
    }
}

std::shared_ptr<Raytracer::ILight> Raytracer::Factory::createLight(const std::string name, LightOptions options)
{
    try {
        std::function function = _lights.at({
            .category = std::string("light"),
            .name = name
        });

        return DLLoader::turnFunctionIntoInstance(function, options);
    } catch (const std::exception &e) {
        throw Exception("Couldn't find " + name);
    }
}
