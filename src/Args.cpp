#include "Args.hpp"
#include "Exception.hpp"
#include <algorithm>
#include <optional>

std::optional<std::string> Raytracer::Args::parseGraphicalLibrary(int argc, char **argv)
{
    for (int i = 2; i < argc; i++) {
        if (std::string(argv[i]) == "--graphical") {
            if (i + 1 >= argc)
                throw Raytracer::Exception("Impossible to parse --graphical argument");
            else {
                std::string libraryName(argv[i + 1]);

                std::transform(libraryName.begin(), libraryName.end(), libraryName.begin(),
                    [](unsigned char c){ return std::tolower(c); });
                return libraryName;
            }
        }
    }
    return std::nullopt;
}
