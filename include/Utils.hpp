#pragma once

#include <string_view>

namespace Raytracer::Utils {
    constexpr std::string_view primitiveEntrypoint("primitiveEntrypoint");
    constexpr std::string_view lightEntrypoint("lightEntrypoint");
    constexpr std::string_view materialEntrypoint("materialEntrypoint");
    constexpr std::string_view transformEntrypoint("transformEntrypoint");

    // Related to the binary path of the raytracer.
    constexpr std::string_view pluginsDir("./plugins");

    constexpr double occlusion = 50.0;
}
