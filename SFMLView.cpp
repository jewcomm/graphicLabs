//
// Created by alexu on 18.11.2022.
//

#include "SFMLView.h"

SFMLView::SFMLView(GraphController *controller) {
    this->controller = controller;
};

int SFMLView::run() {
    sf::RenderWindow window(sf::VideoMode(controller->model->sizeX, controller->model->sizeY), "Labs 1");
    window.setFramerateLimit(60);

    float z = 0;
    float x = 0;
    float y = 0;
    bool showAxis = false;

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) x -= 0.5;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) y -= 0.5;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) z -= 0.5;
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) x += 0.5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) y += 0.5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) z += 0.5;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) x = y = z = 0;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                showAxis = !showAxis;
            }
        }

        controller->reload();
        controller->rotateApp(z);
        controller->rotateOrd(y);
        controller->rotateAbs(x);

        for (auto & i: controller->buffer){
            i = controller->multVecOnMatrix(i, controller->newBasis);
        }

        window.clear();

        std::vector<std::vector<float>> windowBasis = controller->newBasis;

        std::vector<std::vector<float>> output;

        output = controller->convert3Dto2D(controller->buffer);
        std::vector<std::vector<float>> currentBasis = controller->convert3Dto2D(controller->newBasis);

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
                        sf::Vertex(sf::Vector2f(500 + (currentBasis[i][0] - 500) * 100,
                                                500 + (currentBasis[i][1] - 500) * 100), color),
                };
                window.draw(line, 2, sf::Lines);
            }
        }
        window.display();
    }
    return 0;
}