#include "Color.hpp"
#include "Raytracer.hpp"
#include "HitInfo.hpp"
#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include "lights/ILight.hpp"
#include "lights/LightOptions.hpp"
#include "primitives/IPrimitive.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>

Raytracer::Raytracer::Raytracer(const std::string sceneFile) :
    _sceneFile(sceneFile), _config(_sceneFile), rd(), gen(rd())
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
    _toggleAmbiantOcclusion = false;
}

Raytracer::Pixel Raytracer::Raytracer::handleHit(std::shared_ptr<IPrimitive> &obj, HitInfo &hit, size_t left_occlusion, Ray &r, bool isAmbiant, std::shared_ptr<IPrimitive> ignoredObj)
{
    if (isAmbiant == true && obj->getOptions().material->getOptions().properties.reflexion == 0) {
        return Pixel(obj->getOptions().color, 0);
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
        ignoredObj = obj;
        Pixel reflected_pixel = this->mainHandleHit(newRay, left_occlusion - 1, false, ignoredObj);
        ignoredObj = nullptr;
        pixel.color.r = pixel.color.r * (1-reflexion) + reflected_pixel.color.r * reflexion;
        pixel.color.g = pixel.color.g * (1-reflexion) + reflected_pixel.color.g * reflexion;
        pixel.color.b = pixel.color.b * (1-reflexion) + reflected_pixel.color.b * reflexion;
        pixel.multiplier = pixel.multiplier * (1-reflexion) + reflected_pixel.multiplier * reflexion;
    }
    if (obj->getOptions().material->getOptions().properties.transparency >= 0.2) {
        double transparency = obj->getOptions().material->getOptions().properties.transparency;
        ignoredObj = obj;
        Pixel transparent_pixel = this->mainHandleHit(r, left_occlusion - 1, false, ignoredObj);
        ignoredObj = nullptr;
        pixel.color.r = pixel.color.r * (1-transparency) + transparent_pixel.color.r * transparency;
        pixel.color.g = pixel.color.g * (1-transparency) + transparent_pixel.color.g * transparency;
        pixel.color.b = pixel.color.b * (1-transparency) + transparent_pixel.color.b * transparency;
        pixel.multiplier = pixel.multiplier * (1-transparency) + transparent_pixel.multiplier * transparency;
    }
    if (_toggleAmbiantOcclusion == true) {
        // probablement pas la normal qu'on devrait utiliser ici, temporaire
        // utiliser la lambertian distribution plutôt que ce qu'on fait actuellement;
        double multiplierAverage = 0;
        for (size_t i = 0; i < Utils::occlusion; i++) {
            Ray newRay(hit.getHitPos(), Math::Vector3D(normal.x + randomInRange<double>(0, 1) - 0.5, normal.y + randomInRange<double>(0, 1) - 0.5, normal.z + randomInRange<double>(0, 1) - 0.5));
            ignoredObj = obj;
            multiplierAverage += this->mainHandleHit(newRay, left_occlusion - 1, true, ignoredObj).multiplier;
            ignoredObj = nullptr;
        }
        multiplierAverage /= (Utils::occlusion);
        pixel.multiplier += multiplierAverage;
        pixel.multiplier = std::min(pixel.multiplier, 1.0);
    }
    if (isAmbiant == true) {
        pixel.multiplier *= obj->getOptions().material->getOptions().properties.reflexion;
    }
    return pixel;
}

Raytracer::Pixel Raytracer::Raytracer::mainHandleHit(Ray &r, size_t left_occlusion, bool isAmbiant, std::shared_ptr<IPrimitive> ignoredObj)
{
    double currLen = 0;
    double hasHit = false;
    std::shared_ptr<IPrimitive> obj = nullptr;
    HitInfo storedHit;

    for (std::shared_ptr<IPrimitive> &ptr : _primitives) {
        if (ignoredObj != nullptr && ptr.get() == ignoredObj.get()) {
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
    return this->handleHit(obj, storedHit, left_occlusion, r, isAmbiant, ignoredObj);
}

Raytracer::Pixel Raytracer::Raytracer::hitIlluminance(std::shared_ptr<IPrimitive> &s, HitInfo &hit)
{
    Color color = hit.getColor();
    Color white(255,255,255);
    std::vector<Pixel> lightColors;

    for (std::shared_ptr<ILight> &light: _lights) {
        Math::Vector3D light_Vector = light->getDirection(hit.getHitPos());
        Math::Vector3D normal = s->getNormal(hit.getHitPos());
        Color lightColor = light->getOptions().color;
        double tmpMultiplier = light_Vector.cosine(normal);
        if (tmpMultiplier <= 0)
            continue;

        Color tmpColor = white - color;
        tmpColor = Color(std::max(lightColor.r - tmpColor.r, 0), std::max(lightColor.g - tmpColor.g, 0), std::max(lightColor.b - tmpColor.b, 0));

        Ray lightToHit = light->getRay(light_Vector, hit);
        for (std::shared_ptr<IPrimitive> &tmpPrimitive: _primitives) {
            if (tmpPrimitive.get() == s.get())
                continue;
            HitInfo tmpHitInfo = tmpPrimitive->hits(lightToHit);
            if (!tmpHitInfo.hasHit())
                continue;
            // on calcule la norme des deux vecteurs ainsi que le produit scalaire pour voir si le nouvel objet obstruct la lumière
            Math::Vector3D lightToNewObject = light->getDirection(tmpHitInfo.getHitPos());
            light->modifyMultiplierForShadow(light_Vector, lightToNewObject, tmpMultiplier, tmpHitInfo.getMultiplier());

            if (tmpPrimitive->getOptions().material->getOptions().properties.transparency > 0) {
                tmpMultiplier *= tmpPrimitive->getOptions().material->getOptions().properties.transparency;
                continue;
            }
            if (tmpMultiplier == 0.0)
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

void Raytracer::Raytracer::processImage(std::size_t yStart, std::size_t yEnd, std::size_t xStart, std::size_t xEnd)
{
    for (std::size_t y = yStart; y < yEnd; y++) {
        for (std::size_t x = xStart; x < xEnd; x++) {
            double u = static_cast<double>(x) / _camera.width;
            double v = static_cast<double>(y) / _camera.height;
            Ray r = _camera.ray(u, v);
            std::shared_ptr<IPrimitive> ignoredObj;
            this->_pixels[x].push_back(this->mainHandleHit(r, 10, false, ignoredObj)); // le nombre de rebonds est random
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
    unsigned int interval = ::floorf(static_cast<float>(_camera.width) / nproc);
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
            pixel.color = pixel.color * pixel.multiplier;
            std::cout << static_cast<unsigned int>(pixel.color.r) << " "
            << static_cast<unsigned int>(pixel.color.g) << " "
            << static_cast<unsigned int>(pixel.color.b) << std::endl;
        }
    }
}
