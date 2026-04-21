#include "Math/Matrix3x1.hpp"
#include "Math/Vector3D.hpp"
#include "Raytracer.hpp"
#include <exception>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Incorrect amount of arguments" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "--help") {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cout << "    SCENE_FILE: scene configuration" << std::endl;
        return 0;
    }
    try {
        Raytracer::Raytracer raytracer(argv[1]);

        raytracer.exportPPM();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
