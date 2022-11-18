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

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) controller->rotateAbs(true);

        window.clear();

        std::vector<std::vector<float>> output = controller->convert3Dto2D(controller->buffer);

        for (int i = 0; i < output.size() - 1; i++){
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(output[i][0], output[i][1])),
                    sf::Vertex(sf::Vector2f(output[i + 1][0], output[i + 1][1])),
            };
            window.draw(line, 2, sf::Lines);
        }
        window.display();
    }
    return 0;
}