#include "Args.hpp"
#include "Raytracer.hpp"
#include <exception>
#include <iostream>
#include <optional>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Incorrect amount of arguments" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "--help") {
        std::cout << "USAGE: ./raytracer <SCENE_FILE> [--graphical <GRAPHICAL_LIBRARY>]" << std::endl;
        std::cout << "    SCENE_FILE: scene configuration" << std::endl;
        std::cout << "    --graphical <GRAPHICAL_LIBRARY>: Launches the Raytracer with a graphical library" << std::endl;
        return 0;
    }
    try {
        Raytracer::Raytracer raytracer(argv[1]);

        std::optional<std::string> graphicalLib = Raytracer::Args::parseGraphicalLibrary(argc, argv);
        if (graphicalLib.has_value())
            raytracer.launchGraphicalLibrary(graphicalLib.value());
        else
            raytracer.exportPPM();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
