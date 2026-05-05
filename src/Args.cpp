#include "Args.hpp"
#include "Exception.hpp"
#include <optional>

std::optional<std::string> Raytracer::Args::parseGraphicalLibrary(int argc, char **argv)
{
    for (int i = 2; i < argc; i++) {
        if (std::string(argv[i]) == "--graphical") {
            if (i + 1 >= argc)
                throw Raytracer::Exception("Impossible to parse --graphical argument");
            else {
                return std::string(argv[i + 1]);
            }
        }
    }
    return std::nullopt;
}
