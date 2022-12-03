//
// Created by alexu on 18.11.2022.
//

#include "SFMLView.h"

SFMLView::SFMLView(GraphController *controller) {
    this->controller = controller;
}

int SFMLView::run() {
    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "Labs 1");
    window.setFramerateLimit(60);
    sf::Clock clock;

    bool showAxis = false;
    sf::Time axisDelayTime = clock.getElapsedTime();

    sf::Time xoyDelayTime = clock.getElapsedTime();
    sf::Time yozDelayTime = clock.getElapsedTime();
    sf::Time zoxDelayTime = clock.getElapsedTime();

    sf::Time borderDelayTime = clock.getElapsedTime();

    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) controller->angleX -= 0.5;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) controller->angleY -= 0.5;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) controller->angleZ -= 0.5;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) controller->dilationX /= 1.001;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) controller->dilationY /= 1.001;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) controller->dilationZ /= 1.1;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                controller->clear();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                if(clock.getElapsedTime() - xoyDelayTime > sf::milliseconds(500)){
                    controller->invXOY = !controller->invXOY;
                    xoyDelayTime = clock.getElapsedTime();
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                if(clock.getElapsedTime() - yozDelayTime > sf::milliseconds(500)){
                    controller->invYOZ = !controller->invYOZ;
                    yozDelayTime = clock.getElapsedTime();
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
                if(clock.getElapsedTime() - zoxDelayTime > sf::milliseconds(500)){
                    controller->invZOX = !controller->invZOX;
                    zoxDelayTime = clock.getElapsedTime();
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) controller->angleX += 0.5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) controller->angleY += 0.5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) controller->angleZ += 0.5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) controller->dilationX *= 1.001;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) controller->dilationY *= 1.001;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) controller->dilationZ *= 1.1;

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) controller->transfY -= 1;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) controller->transfX -= 1;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) controller->transfZ -= 1;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) controller->transfY += 1;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) controller->transfX += 1;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) controller->transfZ += 1;

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if(clock.getElapsedTime() - axisDelayTime > sf::milliseconds(500)){
                showAxis = !showAxis;
                axisDelayTime = clock.getElapsedTime();
            }
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            if(clock.getElapsedTime() - borderDelayTime > sf::milliseconds(500)){
                controller->showBorder = !controller->showBorder;
                borderDelayTime = clock.getElapsedTime();
            }
        }

        window.clear();

        std::vector<std::vector<float>> windowBasis = controller->newBasis;

        //std::vector<std::vector<float>> output = controller->calcPhysics();

        //output = controller->convert3Dto2D(output, sizeX, sizeY, dist);

        std::vector<std::vector<sf::Vertex>> output = controller->calcPhysics(sizeX, sizeY, dist);

        for(int i = 0; i < output.size(); i++){
            sf::Vertex line[] = {
                    output[i][0], output[i][1]
            };
            window.draw(line, 2, sf::Lines);
        }

        std::vector<std::vector<float>> currentBasis = controller->convert3Dto2D(controller->newBasis, sizeX, sizeY, dist);
        if (showAxis) for (int i = 0; i < currentBasis.size(); i++) {
                sf::Color color;
                if(i == 0) color = sf::Color::Red;
                if(i == 1) color = sf::Color::Green;
                if(i == 2) color = sf::Color::Blue;

                sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(sizeX / 4 + controller->dilationX, 500 + controller->dilationY), color),
                        sf::Vertex(sf::Vector2f(BASIS_COORD(currentBasis[i][0], sizeX / 2) + controller->dilationX,
                                                BASIS_COORD(currentBasis[i][1], sizeY) + controller->dilationY), color),
                };
                window.draw(line, 2, sf::Lines);
            }

        sf::Image zBuffer;
        zBuffer.create(controller->zBufferXSize, controller->zBufferYSize, sf::Color::White);
        for (int i = 0; i < controller->zBufferXSize; i++)
        {
            for(int j = 0; j < controller->zBufferYSize; j++){
                zBuffer.setPixel(i, j, sf::Color::White);
            }
        }

        sf::Texture zTexture;
        sf::Sprite zSprite;
        if(zTexture.loadFromImage(zBuffer)) {
            if (zTexture.create(controller->zBufferXSize, controller->zBufferYSize)) {
                zSprite.setTexture(zTexture, true);
                zSprite.setColor(sf::Color::White);
                window.draw(zSprite);
            }
        }

        window.display();
    }
    return 0;
}