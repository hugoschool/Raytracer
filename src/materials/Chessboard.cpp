#include "materials/Chessboard.hpp"
#include "Color.hpp"
#include "materials/Chessboard.hpp"
#include "materials/AMaterial.hpp"
#include "materials/IMaterial.hpp"
#include <cmath>

Raytracer::Chessboard::Chessboard(Raytracer::MaterialOptions options) : AMaterial(options)
{
    _options.properties.reflexion = 0.1;
}

extern "C" Raytracer::IMaterial *materialEntrypoint(Raytracer::MaterialOptions options)
{
    return new Raytracer::Chessboard(options);
}

Raytracer::Color Raytracer::Chessboard::applyMaterial(Color ac_color, Math::Point3D pos) const
{
    if (std::abs(static_cast<int>(std::floor(pos.x * 0.1)) % 2) == std::abs(static_cast<int>(std::floor((pos.z * 0.1))) % 2) == std::abs(static_cast<int>(std::floor(((pos.y + 1.0) * 0.1))) % 2)) // avec le +1 ça marche donc je le laisse mdr
        return ac_color;
    return Color(0,0,0);
}
