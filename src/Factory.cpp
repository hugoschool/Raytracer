#include "Factory.hpp"
#include "DLLoader.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "graphical/IGraphical.hpp"
#include "graphical/GraphicalOptions.hpp"
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

        // Ignore graphics category, only loaded on createGraphics
        // This is made to prevent memory leaks on load from SFML
        if (config.category == "graphical")
            continue;

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

std::shared_ptr<Raytracer::IGraphical> Raytracer::Factory::createGraphical(const std::string name)
{
    GraphicalOptions options;

    try {
        std::function function = _graphicals.at({
            .category = std::string("graphical"),
            .name = name
        });

        return DLLoader::turnFunctionIntoInstance(function, options);
    } catch (const std::exception &e) {
        // Load the graphical library, as it's not registed in registerAllPlugins
        std::string pluginName = std::string(Utils::pluginsDir) + "/raytracer_graphical_" + name + ".so";

        if (!std::filesystem::exists(pluginName))
            throw Exception("Unknown Graphical plugin" + name);

        std::shared_ptr<DLLoader> loader = std::make_shared<DLLoader>(pluginName);

        if (!loader->symbolExists(std::string(Utils::graphicalEntrypoint)))
            throw Exception("Incorrect plugin " + name);

        _loaders.insert({pluginName, loader});

        PluginConfig config;
        config.category = "graphical";
        config.name = name;

        std::function function = loader->getSymbol<IGraphical, GraphicalOptions>(std::string(Utils::graphicalEntrypoint));

        _graphicals.insert({
            config,
            function
        });

        return DLLoader::turnFunctionIntoInstance(function, options);
    }
}
