#include "graphical/SFML.hpp"
#include "graphical/AGraphical.hpp"
#include "graphical/GraphicalOptions.hpp"
#include "graphical/IGraphical.hpp"
#include "Exception.hpp"
#include <exception>

Raytracer::SFML::SFML() : AGraphical(1920, 1080)
{
    try {
        sf::VideoMode videoMode(sf::Vector2u(_width, _height));

        _window = sf::RenderWindow(videoMode, "Raytracer");
        _window.setFramerateLimit(60);
    } catch (std::exception &e) {
        throw Exception("Something went wrong with the creation of the window");
    }
}

Raytracer::SFML::~SFML()
{
    _window.close();
}

extern "C" Raytracer::IGraphical *graphicalEntrypoint(Raytracer::GraphicalOptions)
{
    return new Raytracer::SFML();
}
