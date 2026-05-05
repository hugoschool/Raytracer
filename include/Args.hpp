#pragma once

#include <string>
#include <optional>

namespace Raytracer {
    class Args {
        public:
            static std::optional<std::string> parseGraphicalLibrary(int argc, char **argv);
    };
}
