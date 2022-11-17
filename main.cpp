#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

//std::vector<std::vector<float>> points = {
//                                        {150, 150, 0},
//                                        {250, 250, 0},
//                                        {250, 150, 0},
//                                        {250, 250, 100},
//                                        {150, 150, 100},
//                                        {150, 250, 100}
//};

std::vector<std::vector<float>> points = {
        {100, 0, 0},
        {100, 100, 0},
        {0, 100, 0},
        {0, 0, 0},
        {100, 0, 0},
        {0, 0, 0},

        {0, 0, 100},
        {0, 100, 100},
        {100, 100, 100},
        {100, 0, 100},

        {100, 0, 0},
        {100, 100, 0},
        {100, 100, 100},
        {0, 100, 100},
        {0, 100, 0},
        {0, 0, 0},
        {0, 0, 100}
};

//std::vector<std::vector<float>> points = {
//        {1, 0, 0, 0},
//        {0, 1, 0, 0},
//        {0, 0, 1, 0},
//        {0, 0, 0, 1}
//};

std::vector<std::vector<float>> pointInNewCoord;

float basisX = 0;
float basisY = 0;

float sizeX = 1000;
float sizeY = 1000;

float dist = 1000;

float grad = 30;
float gradSin = sinf(grad * M_PI / 180);
float gradCos = cosf(grad * M_PI / 180);

std::vector<std::vector<float>> rotate = {
        {gradCos, 0, 0-gradSin, 0},
        {0, 1, 0, 0},
        {gradSin, 0, gradCos, 0},
        {0, 0, 0, 1}
};

std::vector<std::vector<float>> rabs = {
        {gradCos, gradSin, 0, 0},
        {0-gradSin, gradCos, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
};

std::vector<std::vector<float>> rabsciss = {
        {1, 0, 0, 1},
        {0, gradCos, gradSin, 0},
        {0, 0-gradSin, gradCos, 0},
        {0, 0, 0, 1}
};

std::vector<float> mult(std::vector<float>v, std::vector<std::vector<float>> m){
    std::vector<float> res;
    v.push_back(1);
    for(int i = 0; i < v.size(); i++){
        float temp = 0;
        for(int j = 0; j < v.size(); j++){
            temp += m[i][j] * v[j];
        }
        res.push_back(temp);
    }
    return res;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "Lab's 1 graphic affine processing");

    std::vector<std::vector<float>> aftR1;
    for(int i = 0; i < points.size(); i++){
        std::vector<float> res = mult(points[i], rotate);
        //std::vector<float> res = mult(std::vector<float>({3,2,1}), points);
        aftR1.push_back(res);
    }

    std::vector<std::vector<float>> aftR2;
    for(int i = 0; i < aftR1.size(); i++){
        aftR1[i].pop_back();
        std::vector<float> res = mult(aftR1[i], rabs);
        //std::vector<float> res = mult(std::vector<float>({3,2,1}), points);
        aftR2.push_back(res);
    }

    std::vector<std::vector<float>> aftR;
    for(int i = 0; i < aftR2.size(); i++){
        aftR2[i].pop_back();
        std::vector<float> res = mult(aftR2[i], rabs);
        //std::vector<float> res = mult(std::vector<float>({3,2,1}), points);
        aftR.push_back(res);
    }

    for(int i = 0; i < points.size(); i++){
        std::vector<float> t;
        float x = aftR[i][0];
        float y = aftR[i][1];
        float z = aftR[i][2];
        float mX = sizeX / 4 + x * dist / (z + dist);
        float mY = sizeY / 2 - y * dist / (z + dist);
        t.push_back(mX);
        t.push_back(mY);
        pointInNewCoord.push_back(t);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < pointInNewCoord.size() - 1; i++){
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(basisX + pointInNewCoord[i][0], basisY + pointInNewCoord[i][1])),
                    sf::Vertex(sf::Vector2f(basisX + pointInNewCoord[i + 1][0], basisY + pointInNewCoord[i + 1][1]))
            };
            window.draw(line, 2, sf::Lines);
        }
//        sf::Vertex line[] = {
//                sf::Vertex(sf::Vector2f(basisX + points[points.size() - 1][0], basisY + points[points.size() - 1][1])),
//                sf::Vertex(sf::Vector2f(basisX + points[0][0], basisY + points[0][1]))
//        };
//        window.draw(line, 2, sf::Lines);
        window.display();
    }
    return 0;
}