#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(120.f);
//    shape.setFillColor(sf::Color::Green);

    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(10, 10)),
            sf::Vertex(sf::Vector2f(20, 30))
    };
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(line, 2, sf::Lines);
        window.display();
    }
    return 0;
}