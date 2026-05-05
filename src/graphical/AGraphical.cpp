#include "graphical/AGraphical.hpp"

Raytracer::AGraphical::AGraphical::AGraphical(std::size_t width, std::size_t height) :
    _width(width), _height(height)
{
}

Raytracer::AGraphical::AGraphical::~AGraphical()
{
}

void Raytracer::AGraphical::displayPixels(std::vector<std::vector<Pixel>> &)
{
}

void Raytracer::AGraphical::handleEvents()
{
}

bool Raytracer::AGraphical::isOpen()
{
    return false;
}

