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

//    float z = 0;
//    float x = 0;
//    float y = 0;

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) controller->rotateAbs(-0.003);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) controller->rotateApp(-0.003);
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) controller->rotateOrd(-0.003);
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) controller->rotateAbs(0.003);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) controller->rotateApp(0.003);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) controller->rotateOrd(0.003);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) controller->reload();
        }

        window.clear();

        std::vector<std::vector<float>> windowBasis = controller->newBasis;
//        for(auto & i : windowBasis) {
//            i = controller->multMatrixOnVec(controller->model->basis , i);
//        }

        std::vector<std::vector<float>> output;

        for(auto & i : controller->buffer) {
            output.push_back(controller->multMatrixOnVec(windowBasis, i));
        }

        windowBasis = controller->inverseMatrix(windowBasis);

        for(auto & i : output) {
            i = controller->multMatrixOnVec(windowBasis, i);
        }

        output = controller->convert3Dto2D(output);
        std::vector<std::vector<float>> currentBasis = controller->convert3Dto2D(controller->newBasis);

        for (int i = 0; i < output.size() - 1; i++){
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(output[i][0], output[i][1])),
                    sf::Vertex(sf::Vector2f(output[i + 1][0], output[i + 1][1])),
            };
            window.draw(line, 2, sf::Lines);
        }
        for(int i = 0; i < currentBasis.size(); i++){
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(500, 500)),
                    sf::Vertex(sf::Vector2f(500 + (currentBasis[i][0] - 500) * 100, 500 + (currentBasis[i][1] - 500) * 100)),
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }
    return 0;
}