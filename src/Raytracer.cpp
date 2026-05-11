#include "Color.hpp"
#include "Raytracer.hpp"
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "lights/ILight.hpp"
#include "lights/LightOptions.hpp"
#include "primitives/IPrimitive.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

#define OCCLUSION 50.0

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(_sceneFile)
{
    _camera = _config.parseCamera();
    _primitives = _config.parsePrimitives();
    _pixels.reserve(_camera.width * _camera.height);
    // To be changed, this is only temporary as this is highly unefficient and only works for sphere collisions
    std::sort(_primitives.begin(), _primitives.end(), [](std::shared_ptr<IPrimitive> &a, std::shared_ptr<IPrimitive> &b)
    {
        return a->getOptions().center.z > b->getOptions().center.z;
    });
    _lights = _config.parseLights();
    _ignored_object = nullptr;
    _toggleAmbiantOcclusion = false;
}

double Raytracer::Raytracer::random(double lower, double higher)
{
    std::uniform_real_distribution<double> randomnb(lower,higher);
    std::default_random_engine randomEngine;
    return randomnb(randomEngine);
}

Raytracer::Pixel Raytracer::Raytracer::handleHit(std::shared_ptr<IPrimitive> &obj, HitInfo &hit, size_t left_occlusion, Ray &r, bool isAmbiant)
{
    if (isAmbiant == true && obj->getOptions().material->getOptions().properties.reflexion == 0) {
        return Pixel(obj->getOptions().color, 0);
    }
    if (this->_colorCache.contains(std::tuple(hit.getHitPos().x, hit.getHitPos().y, hit.getHitPos().z)) == true && this->_colorCache.at(std::tuple(hit.getHitPos().x, hit.getHitPos().y, hit.getHitPos().z)).second <= left_occlusion) {
        Pixel pixel = this->_colorCache.at(std::tuple(hit.getHitPos().x, hit.getHitPos().y, hit.getHitPos().z)).first;
        if (isAmbiant == true)
            pixel.multiplier *= obj->getOptions().material->getOptions().properties.reflexion;
        return pixel;
    }
    Pixel pixel = this->hitIlluminance(obj, hit);

    if (left_occlusion == 0) {
        if (isAmbiant == true)
            pixel.multiplier *= obj->getOptions().material->getOptions().properties.reflexion;
        return pixel;
    }

    Math::Vector3D normal = obj->getNormal(hit.getHitPos());

    if (obj->getOptions().material->getOptions().properties.reflexion >= 0.20) {
        Math::Vector3D newDirection = (r.direction) - normal * 2 * ((r.direction).dot(normal));
        Math::Point3D newPosition = hit.getHitPos() + newDirection * 0; // pour éviter que le vecteur ne se retouche
        newDirection = newDirection / newDirection.length();
        Ray newRay(newPosition, newDirection);
        double reflexion = obj->getOptions().material->getOptions().properties.reflexion;
        _ignored_object = obj;
        Pixel reflected_pixel = this->mainHandleHit(newRay, left_occlusion - 1, false);
        _ignored_object = nullptr;
        pixel.color.r = pixel.color.r * (1-reflexion) + reflected_pixel.color.r * reflexion;
        pixel.color.g = pixel.color.g * (1-reflexion) + reflected_pixel.color.g * reflexion;
        pixel.color.b = pixel.color.b * (1-reflexion) + reflected_pixel.color.b * reflexion;
        pixel.multiplier = pixel.multiplier * (1-reflexion) + reflected_pixel.multiplier * reflexion;
    }
    if (obj->getOptions().material->getOptions().properties.transparency >= 0.2) {
        double transparency = obj->getOptions().material->getOptions().properties.transparency;
        _ignored_object = obj;
        Pixel transparent_pixel = this->mainHandleHit(r, left_occlusion - 1, false);
        _ignored_object = nullptr;
        pixel.color.r = pixel.color.r * (1-transparency) + transparent_pixel.color.r * transparency;
        pixel.color.g = pixel.color.g * (1-transparency) + transparent_pixel.color.g * transparency;
        pixel.color.b = pixel.color.b * (1-transparency) + transparent_pixel.color.b * transparency;
        pixel.multiplier = pixel.multiplier * (1-transparency) + transparent_pixel.multiplier * transparency;
    }
    if (_toggleAmbiantOcclusion == true) {
        // probablement pas la normal qu'on devrait utiliser ici, temporaire
        // utiliser la lambertian distribution plutôt que ce qu'on fait actuellement;
        double multiplierAverage = 0;
        for (size_t i = 0; i < OCCLUSION; i++) {
            Ray newRay(hit.getHitPos(), Math::Vector3D(normal.x + random(0,1) - 0.5, normal.y + random(0,1) - 0.5, normal.z + random(0,1) - 0.5));
            _ignored_object = obj;
            multiplierAverage += this->mainHandleHit(newRay, left_occlusion - 1, true).multiplier;
            _ignored_object = nullptr;
        }
        multiplierAverage /= (OCCLUSION);
        pixel.multiplier += multiplierAverage;
        pixel.multiplier = std::min(pixel.multiplier, 1.0);
    }
    if (isAmbiant == true) {
        pixel.multiplier *= obj->getOptions().material->getOptions().properties.reflexion;
    }
    this->_colorCache.emplace(std::pair(std::tuple(hit.getHitPos().x, hit.getHitPos().y, hit.getHitPos().z), std::pair(pixel, left_occlusion)));
    return pixel;
}

Raytracer::Pixel Raytracer::Raytracer::mainHandleHit(Ray &r, size_t left_occlusion, bool isAmbiant)
{
    double currLen = 0;
    double hasHit = false;
    std::shared_ptr<IPrimitive> obj = nullptr;
    HitInfo storedHit;

    for (std::shared_ptr<IPrimitive> &ptr : _primitives) {
        if (_ignored_object != nullptr && ptr.get() == _ignored_object.get()) {
            continue;
        }
        HitInfo hit = ptr->hits(r);
        if (hit.hasHit()) {
            if (currLen != 0 && currLen < (hit.getHitPos() - r.origin).length())
                continue;
            currLen = (hit.getHitPos() - r.origin).length();
            hasHit = true;
            obj = ptr;
            storedHit = hit;
        }
    }
    if (!hasHit)
        return Pixel(Color(0,0,0), 1);
    // comme ça on fait le calcul qu'une fois qu'on a déterminé le plus proche;
    return this->handleHit(obj, storedHit, left_occlusion, r, isAmbiant);
}

Raytracer::Pixel Raytracer::Raytracer::hitIlluminance(std::shared_ptr<IPrimitive> &s, HitInfo &hit)
{
    Color color = hit.getColor();
    Color white(255,255,255);
    std::vector<Pixel> lightColors;

    for (std::shared_ptr<ILight> &light: _lights) {
        Math::Vector3D light_Vector = light->getOptions().position - hit.getHitPos();
        Math::Vector3D normal = s->getNormal(hit.getHitPos());
        Color lightColor = light->getOptions().color;
        double tmpMultiplier = light_Vector.cosine(normal);
        if (tmpMultiplier <= 0)
            continue;

        Color tmpColor = white - color;
        tmpColor = Color(std::max(lightColor.r - tmpColor.r, 0), std::max(lightColor.g - tmpColor.g, 0), std::max(lightColor.b - tmpColor.b, 0));
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
            if (tmpPrimitive->getOptions().material->getOptions().properties.transparency > 0) {
                tmpMultiplier *= tmpPrimitive->getOptions().material->getOptions().properties.transparency;
                continue;
            }
            tmpMultiplier = 0.0;
            break;
        }
        if (tmpMultiplier <= 0.01) {
            continue;
        }
        lightColors.push_back(Pixel(tmpColor, tmpMultiplier));
    }
    if (lightColors.size() == 0) {
        return Pixel(color, 0);
    }
    double multiplier = 0;
    for (auto &it: lightColors) {
        multiplier += it.multiplier;
        color.r = std::max(color.r, it.color.r);
        color.g = std::max(color.g, it.color.g);
        color.b = std::max(color.b, it.color.b);
    }
    // multiplier /= _lights.size();
    multiplier = std::min(multiplier, 1.0);
    return Pixel(color, multiplier);
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
            this->_pixels.push_back(this->mainHandleHit(r, 10, false)); // le nombre de rebonds est random
        }
    }
    for (auto &it: _pixels) {
        std::cout << static_cast<unsigned int>(it.color.r * it.multiplier) << " " 
        << static_cast<unsigned int>(it.color.g * it.multiplier) << " "
        << static_cast<unsigned int>(it.color.b * it.multiplier) << std::endl;
    }
}
