#include "HitInfo.hpp"
#include "Color.hpp"
#include "Math/Point3D.hpp"

Raytracer::HitInfo::HitInfo(bool didHit, Math::Point3D &pos, Color &color): _hasHit(didHit), _hitPos(pos), _color(color)
{
    
}

Raytracer::HitInfo::HitInfo(bool didHit) : _hasHit(didHit), _hitPos(), _color()
{
}

bool Raytracer::HitInfo::hasHit() const
{
    return this->_hasHit;
}

Raytracer::Color Raytracer::HitInfo::getColor() const
{
    return this->_color;
}

Raytracer::Math::Point3D Raytracer::HitInfo::getHitPos() const
{
    return this->_hitPos;
}