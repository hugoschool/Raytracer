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
#include <cstddef>
#include <iostream>
#include <memory>
#include <random>
#include <utility>
#include <vector>

#define OCCLUSION 10

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(_sceneFile), _maxilluminance(1.0)
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
}
double random(double lower, double higher)
{
    std::uniform_real_distribution<double> randomnb(lower,higher);
    std::default_random_engine randomEngine;
    return randomnb(randomEngine);
}


Raytracer::Color Raytracer::Raytracer::handleHitOther(std::shared_ptr<IPrimitive> &obj, HitInfo &hit, size_t left_occlusion, Ray &r)
{

    // if (this->_colorCache.contains(std::tuple(hit.getHitPos().x, hit.getHitPos().y, hit.getHitPos().z)) == true) {
        // return this->_colorCache.at(std::tuple(hit.getHitPos().x, hit.getHitPos().y, hit.getHitPos().z));
    // }
    Color color = this->hitIlluminance(obj, hit);

    if (left_occlusion == 0) {
        return color;
    }

    Math::Vector3D normal = obj->getNormal(hit.getHitPos());
    Math::Vector3D newDirection = (r.direction) - normal * 2 * ((r.direction).dot(normal));
    Math::Point3D newPosition = hit.getHitPos() + normal * 1; // pour éviter que le vecteur ne se retouche
    Ray newRay(newPosition, newDirection);
    // test pour vérifier la transparence
    _ignored_object = obj;
    Color reflected_color = this->mainHandleHit(newRay, left_occlusion - 1);
    _ignored_object = nullptr;
    // pour une reflective de 50%
    if (reflected_color.r == 0 && reflected_color.b == 0 && reflected_color.g == 0)
        return color;
    color.r = color.r * 0.5 + reflected_color.r * 0.5;
    color.g = color.g * 0.5 + reflected_color.g * 0.5;
    color.b = color.b * 0.5 + reflected_color.b * 0.5;
    return color;
    // probablement pas la normal qu'on devrait utiliser ici, temporaire
    // utiliser la lambertian distribution plutôt que ce qu'on fait actuellement;
    // for (size_t i = 0; i < OCCLUSION; i++) {
    //     Ray newRay(hit.getHitPos(), Math::Vector3D(normal.x + random(0,1) - 0.5, normal.y + random(0,1) - 0.5, normal.z + random(0,1) - 0.5));
    //     allColors.push_back(this->mainHandleHit(newRay, left_occlusion - 1));
    // }
    // double red = 0;
    // double blue = 0;
    // double green = 0;
    // double allMultiplier = 0;
    // for (auto &it: allColors)  {
    //     red += it.multiplier * it.color.r;
    //     blue += it.multiplier * it.color.b;
    //     green += it.multiplier * it.color.g;
    //     allMultiplier += it.multiplier;
    // }
    // allMultiplier /= allColors.size();
    // double tmpMax = std::max(std::max(red, blue), green);
    // red /= tmpMax;
    // blue /= tmpMax;
    // green /= tmpMax;
    // //changer les valeurs de multiplication en fonction du % d'occlusion qu'on veut
    // color.r = color.r * 0.70 * multiplier + red * 0.30 * allMultiplier;
    // color.g = color.g * 0.70 * multiplier + green * 0.30 * allMultiplier;
    // color.b = color.b * 0.70 * multiplier + blue * 0.30 * allMultiplier;
    // multiplier = (multiplier + allMultiplier) / 2;
    // this->_colorCache.emplace(std::tuple(hit.getHitPos().x, hit.getHitPos().y, hit.getHitPos().z), pixel);
}

Raytracer::Color Raytracer::Raytracer::mainHandleHit(Ray &r, size_t left_occlusion)
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
        return Color(0,0,0);
    // comme ça on fait le calcul qu'une fois qu'on a déterminé le plus proche;
    return this->handleHitOther(obj, storedHit, left_occlusion, r);
}

Raytracer::Color Raytracer::Raytracer::hitIlluminance(std::shared_ptr<IPrimitive> &s, HitInfo &hit)
{
    Color color = hit.getColor();
    int r = 0;
    int g = 0;
    int b = 0;
    for (std::shared_ptr<ILight> &light: _lights) {
        Math::Vector3D light_Vector = light->getOptions().position - hit.getHitPos();
        Math::Vector3D normal = s->getNormal(hit.getHitPos());
        Color lightColor = light->getOptions().color;
        double tmpMultiplier = light_Vector.cosine(normal);
        if (tmpMultiplier <= 0)
            continue;
        Math::Vector3D colorVector = (Math::Vector3D(color) / Math::Vector3D(color).length()) * tmpMultiplier;
        Color tmpColor = Color(colorVector.x * lightColor.r, colorVector.y * lightColor.g, colorVector.z * lightColor.b);
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
        r += tmpColor.r;
        g += tmpColor.g;
        b += tmpColor.b;
    }
    return Color(static_cast<unsigned char>(std::min(r, 255)), static_cast<unsigned short>(std::min(g, 255)), static_cast<unsigned short>(std::min(b,255)));
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
            this->_pixels.push_back(this->mainHandleHit(r, 5)); // nombre random pour l'instant
        }
    }
    for (auto &it: _pixels) {
        std::cout << static_cast<unsigned int>(it.r) << " " 
        << static_cast<unsigned int>(it.g) << " "
        << static_cast<unsigned int>(it.b) << std::endl;
    }
}
