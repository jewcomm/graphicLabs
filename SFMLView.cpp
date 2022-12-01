//
// Created by alexu on 18.11.2022.
//

#include "SFMLView.h"

SFMLView::SFMLView(GraphController *controller) {
    this->controller = controller;
};

int SFMLView::run() {
    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "Labs 1");
    window.setFramerateLimit(60);

    float z = 0;
    float x = 0;
    float y = 0;

    float a = 1;
    float b = 1;
    float c = 1;

    bool showAxis = false;


    float ax = 0;
    float by = 0;
    float cz = 0;
    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) x -= 0.5;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) y -= 0.5;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) z -= 0.5;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) a /= 1.001;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) b /= 1.001;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) c /= 1.1;
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) x += 0.5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) y += 0.5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) z += 0.5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) a *= 1.001;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) b *= 1.001;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) c *= 1.1;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ax += 1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) by += 1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) cz += 1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ax -= 1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) by -= 1;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) cz -= 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                x = y = z = 0;
                a = b = c = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                showAxis = !showAxis;
            }
        }

        controller->reload();
        controller->rotateApp(z);
        controller->rotateOrd(y);
        controller->rotateAbs(x);
        controller->comprStret(a, b, c);
        controller->transfer(ax, by, cz);

        for (auto & i: controller->buffer){
            i = controller->multVecOnMatrix(i, controller->newBasis);
        }

        window.clear();

        std::vector<std::vector<float>> windowBasis = controller->newBasis;

        std::vector<std::vector<float>> output;

        output = controller->convert3Dto2D(controller->buffer, sizeX, sizeY, dist);
        std::vector<std::vector<float>> currentBasis = controller->convert3Dto2D(controller->newBasis, sizeX, sizeY, dist);

        for (int i = 0; i < output.size() - 1; i++){
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(output[i][0], output[i][1])),
                    sf::Vertex(sf::Vector2f(output[i + 1][0], output[i + 1][1])),
            };
            window.draw(line, 2, sf::Lines);
        }
        if(showAxis) {
            for (int i = 0; i < currentBasis.size(); i++) {
                sf::Color color;
                if(i == 0) color = sf::Color::Red;
                if(i == 1) color = sf::Color::Green;
                if(i == 2) color = sf::Color::Blue;

                sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(500, 500), color),
                        sf::Vertex(sf::Vector2f(BASIS_COORD(currentBasis[i][0]),
                                                BASIS_COORD(currentBasis[i][1])), color),
                };
                window.draw(line, 2, sf::Lines);
            }
        }
        window.display();
    }
    return 0;
}