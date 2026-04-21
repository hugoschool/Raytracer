#include "Raytracer.hpp"

Raytracer::Raytracer::Raytracer(const std::string sceneFile) : _sceneFile(sceneFile), _config()
{
    _config.readFile(_sceneFile);
}

void Raytracer::Raytracer::exportPPM()
{
}
