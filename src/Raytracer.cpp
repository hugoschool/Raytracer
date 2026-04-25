#include "Color.hpp"
#include "Raytracer.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "lights/ILight.hpp"
#include "lights/LightOptions.hpp"
#include "primitives/IPrimitive.hpp"
#include <algorithm>
#include <iostream>
#include <memory>

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(_sceneFile)
{
    _camera = _config.parseCamera();
    _primitives = _config.parsePrimitives();

    // To be changed, this is only temporary as this is highly unefficient and only works for sphere collisions
    std::sort(_primitives.begin(), _primitives.end(), [](std::shared_ptr<IPrimitive> &a, std::shared_ptr<IPrimitive> &b)
    {
        return a->getOptions().center.z > b->getOptions().center.z;
    });

    _lights = _config.parseLights();
}


void Raytracer::Raytracer::handleHit(std::shared_ptr<IPrimitive> &s, HitInfo &hit, Color &color)
{
    color = hit.getColor();
    double multiplier = 0.0;
    for (std::shared_ptr<ILight> &light: _lights) {
        Math::Vector3D light_Vector = light->getOptions().position - hit.getHitPos();
        Math::Vector3D normal = s->getNormal(hit.getHitPos());
        double tmpMultiplier = light_Vector.cosine(normal);
        if (tmpMultiplier <= 0)
            continue;
        Ray lightToHit(light->getOptions().position, light_Vector);
        for (std::shared_ptr<IPrimitive> &tmpSphere: _primitives) {
            if (tmpSphere.get() == s.get())
                continue;
            HitInfo tmpHitInfo = tmpSphere->hits(lightToHit);
            if (!tmpHitInfo.hasHit())
                continue;
            // on calcule la norme des deux vecteurs ainsi que le produit scalaire pour voir si le nouvel objet obstruct la lumière
            Math::Vector3D lightToNewObject = light->getOptions().position - tmpHitInfo.getHitPos();
            if (lightToNewObject.length() > light_Vector.length())
                continue;
            if (lightToNewObject.dot(light_Vector) > 0)
                continue;
            tmpMultiplier = 0.0;
            break;
        }
        multiplier = std::max(multiplier, tmpMultiplier);
    }

    multiplier = std::min(1.0, multiplier);
    color = color * multiplier;
}

void Raytracer::Raytracer::exportPPM()
{
    std::cout << "P3" << std::endl;
    std::cout << _camera.width << " " << _camera.height << std::endl;
    std::cout << "255" << std::endl;

    for (std::size_t y = 0; y < _camera.height; y++) {
        for (std::size_t x = 0; x < _camera.width; x++) {
            double u = static_cast<double>(x) / _camera.width;
            double v = static_cast<double>(y) / _camera.height;
            Ray r = _camera.ray(u, v);

            bool hasHit = false;
            Color color;
            for (std::shared_ptr<IPrimitive> &ptr : _primitives) {
                HitInfo hit = ptr->hits(r);
                if (hit.hasHit()) {
                    this->handleHit(ptr, hit, color);
                    hasHit = true;
                    break;
                }
            }

            if (hasHit) {
                std::cout   << static_cast<unsigned int>(color.r) << " "
                            << static_cast<unsigned int>(color.g) << " "
                            << static_cast<unsigned int>(color.b) << std::endl;
            } else
                std::cout << "0 0 0" << std::endl;
        }
    }
}
