#pragma once

#include "graphical/AGraphical.hpp"
#include <SFML/Graphics.hpp>

namespace Raytracer {
    class SFML : public AGraphical {
        public:
            SFML();
            ~SFML();

        private:
            sf::RenderWindow _window;
    };
}
