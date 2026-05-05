#include "graphical/SFML.hpp"
#include "Pixel.hpp"
#include "graphical/AGraphical.hpp"
#include "graphical/GraphicalOptions.hpp"
#include "graphical/IGraphical.hpp"
#include "Exception.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
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

bool Raytracer::SFML::isOpen()
{
    return _window.isOpen();
}

void Raytracer::SFML::handleEvents()
{
    while (const std::optional event = _window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            _window.close();
    }
}

void Raytracer::SFML::displayPixels(std::vector<std::vector<Pixel>> &pixels)
{
    _window.clear();

    sf::Image image = sf::Image(sf::Vector2u(_width, _height));

    for (unsigned int x = 0; x < _width && x < pixels.size(); x++) {
        for (unsigned int y = 0; y < _height && y < pixels[x].size(); y++) {
            Pixel &pixel = pixels.at(x).at(y);
            image.setPixel(sf::Vector2u(x, y), sf::Color(
                pixel.color.r,
                pixel.color.g,
                pixel.color.b,
                255
            ));
        }
    }

    sf::Texture texture(image);
    _window.draw(sf::Sprite(texture));
    _window.display();
}

extern "C" Raytracer::IGraphical *graphicalEntrypoint(Raytracer::GraphicalOptions)
{
    return new Raytracer::SFML();
}
