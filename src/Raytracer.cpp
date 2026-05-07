#include "Color.hpp"
#include "Raytracer.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "lights/ILight.hpp"
#include "lights/LightOptions.hpp"
#include "primitives/IPrimitive.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <thread>

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(_sceneFile), _maxilluminance(1.0)
{
    _config.parseIncludes();
    _camera = _config.parseCamera();
    _primitives = _config.parsePrimitives();
    // To be changed, this is only temporary as this is highly unefficient and only works for sphere collisions
    std::sort(_primitives.begin(), _primitives.end(), [](std::shared_ptr<IPrimitive> &a, std::shared_ptr<IPrimitive> &b)
    {
        return a->getOptions().center.z > b->getOptions().center.z;
    });

    _lights = _config.parseLights();
}

Raytracer::Pixel Raytracer::Raytracer::handleHit(std::shared_ptr<IPrimitive> &s, HitInfo &hit, Color &color)
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
        for (std::shared_ptr<IPrimitive> &tmpPrimitive: _primitives) {
            if (tmpPrimitive.get() == s.get())
                continue;
            HitInfo tmpHitInfo = tmpPrimitive->hits(lightToHit);
            if (!tmpHitInfo.hasHit())
                continue;
            // on calcule la norme des deux vecteurs ainsi que le produit scalaire pour voir si le nouvel objet obstruct la lumière
            Math::Vector3D lightToNewObject = light->getOptions().position - tmpHitInfo.getHitPos();
            if (lightToNewObject.length() > light_Vector.length()) {
                continue;
            }
            if (light_Vector.dot(lightToNewObject) < 0) // On calcule la norme pour savoir si les vecteurs sont opposés
                continue;
            tmpMultiplier = 0.0;
            break;
        }
        multiplier += tmpMultiplier;
    }
    if (this->_maxilluminance < multiplier)
        this->_maxilluminance = multiplier;
    return Pixel {
        .color = color,
        .multiplier = multiplier,
    };
}

void Raytracer::Raytracer::processImage(std::size_t yStart, std::size_t yEnd, std::size_t xStart, std::size_t xEnd)
{
    for (std::size_t y = yStart; y < yEnd; y++) {
        for (std::size_t x = xStart; x < xEnd; x++) {
            double u = static_cast<double>(x) / _camera.width;
            double v = static_cast<double>(y) / _camera.height;
            Ray r = _camera.ray(u, v);

            Color color;
            double currLen = 0;
            bool hasHit = false;

            for (std::shared_ptr<IPrimitive> &ptr : _primitives) {
                HitInfo hit = ptr->hits(r);
                if (hit.hasHit()) {
                    if (currLen != 0 && currLen < (hit.getHitPos() - r.origin).length())
                        continue;
                    if (hasHit == true)
                        _pixels[x].pop_back();
                    Pixel pixel = this->handleHit(ptr, hit, color);
                    _pixels[x].push_back(pixel);
                    currLen = (hit.getHitPos() - r.origin).length();
                    hasHit = true;
                }
            }

            if (hasHit == false) {
                _pixels[x].push_back(Pixel{.color = Color(0,0,0), .multiplier = 0});
            }

        }
    }
}

void Raytracer::Raytracer::exportPPM()
{
    std::cout << "P3" << std::endl;
    std::cout << _camera.width << " " << _camera.height << std::endl;
    std::cout << "255" << std::endl;

    unsigned int nproc = std::thread::hardware_concurrency();

    // In case hardware_concurrency fails
    if (nproc == 0)
        nproc = 1;

    std::vector<std::thread> threads;
    threads.reserve(nproc);

    unsigned int xStart = 0;
    unsigned int interval = std::floorf(static_cast<float>(_camera.width) / nproc);
    unsigned int xEnd = interval;
    unsigned int compensation = _camera.width % nproc;

    _pixels.reserve(_camera.width);

    for (unsigned int x = 0; x < _camera.width; x++) {
        std::vector<Pixel> line;
        line.reserve(_camera.height);
        _pixels.push_back(line);
    }

    for (unsigned int i = 0; i < nproc; i++) {
        threads.push_back(std::thread(&Raytracer::processImage, this, 0, _camera.height, xStart, xEnd));
        xStart = xEnd;
        xEnd += interval;
        if (i + 1 == nproc - 1)
            xEnd += compensation;
    }

    for (std::thread &thread : threads) {
        thread.join();
    }

    for (unsigned int y = 0; y < _camera.height; y++) {
        for (unsigned int x = 0; x < _camera.width; x++) {
            Pixel pixel = _pixels.at(x).at(y);
            pixel.multiplier /= this->_maxilluminance;
            pixel.color = pixel.color * pixel.multiplier;
            std::cout << static_cast<unsigned int>(pixel.color.r) << " "
            << static_cast<unsigned int>(pixel.color.g) << " "
            << static_cast<unsigned int>(pixel.color.b) << std::endl;
        }
    }
}
