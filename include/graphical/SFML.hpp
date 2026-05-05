#pragma once

#include "graphical/AGraphical.hpp"
#include <SFML/Graphics.hpp>

namespace Raytracer {
    class SFML : public AGraphical {
        public:
            SFML();
            ~SFML();

            bool isOpen() override;
            void handleEvents() override;
            void displayPixels(std::vector<std::vector<Pixel>> &) override;

        private:
            sf::RenderWindow _window;
    };
}
