#pragma once

#include <string_view>

namespace Raytracer::Utils {
    constexpr std::string_view primitiveEntrypoint("primitiveEntrypoint");
    constexpr std::string_view lightEntrypoint("lightEntrypoint");

    // Related to the binary path of the raytracer.
    constexpr std::string_view pluginsDir("./plugins");
}
