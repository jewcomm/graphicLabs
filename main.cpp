#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

std::vector<std::vector<float>> points = {
        //X     Y       Z
        {100,   0,      0},
        {100,   100,    0},
        {0,     100,    0},
        {0,     0,      0},
        {100,   0,      0},
        {0,     0,      0},

        {0,     0,      100},
        {0,     100,    100},
        {100,   100,    100},
        {100,   0,      100},
        {0,     0,      100},
        {100,   0,      100},

        {100,   0,      0},
        {100,   100,    0},
        {100,   100,    100},
        {0,     100,    100},
        {0,     100,    0},
        {0,     0,      0},
        {0,     0,      100}
};

std::vector<std::vector<float>> basis = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
};

float sizeX = 1000;
float sizeY = 1000;

float dist = 1000;

std::vector<std::vector<float>> rotateAbs(float angle){
    float sinFI = sinf(angle * M_PI / 180);
    float cosFI = cosf(angle * M_PI / 180);
    return {{1, 0, 0, 1},
            {0, cosFI, sinFI, 0},
            {0, 0-sinFI, cosFI, 0},
            {0, 0, 0, 1}};
}

std::vector<std::vector<float>> rotateOrd(float angle){
    float sinFI = sinf(angle * M_PI / 180);
    float cosFI = cosf(angle * M_PI / 180);
    return {
            {cosFI, sinFI, 0, 0},
            {0-sinFI, cosFI, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };
}

std::vector<std::vector<float>> rotateApp(float angle){
    float sinFI = sinf(angle * M_PI / 180);
    float cosFI = cosf(angle * M_PI / 180);
    return {
            {cosFI, 0, 0-sinFI, 0},
            {0, 1, 0, 0},
            {sinFI, 0, cosFI, 0},
            {0, 0, 0, 1}
    };
}


std::vector<float> multVecOnMatrix(std::vector<float>v, std::vector<std::vector<float>> m){
    std::vector<float> res;
    v.push_back(1);
    for(int i = 0; i < m.size(); i++){
        float temp = 0;
        for(int j = 0; j < m.size(); j++){
            temp += m[i][j] * v[j];
        }
        res.push_back(temp);
    }
    res.pop_back();
    return res;
}

std::vector<std::vector<float>> convert3Dto2D(std::vector<std::vector<float>> input){
    std::vector<std::vector<float>> result;
    for(int i = 0; i < input.size(); i++){
        float mX = sizeX / 2 + input[i][0] * dist / (input[i][3] + dist);
        float mY = sizeY / 2 + input[i][1] * dist / (input[i][3] + dist);
        result.push_back(std::vector<float>({mX, mY}));
    }
    return result;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "Lab's 1 graphic affine processing");

    window.setFramerateLimit(60);

    float t = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

//        std::vector<std::vector<float>> f;
//
//        for(int i = 0; i < points.size(); i++){
//            f.push_back(multVecOnMatrix(points[i], rotateApp(t)));
//        }
//
//        std::vector<std::vector<float>> k;
//
//        for(int i = 0; i < f.size(); i++){
//            k.push_back(multVecOnMatrix(f[i], rotateAbs(t)));
//        }
//
//        std::vector<std::vector<float>> g;
//
//        for(int i = 0; i < k.size(); i++){
//            g.push_back(multVecOnMatrix(k[i], rotateOrd(t)));
//        }
//
//        std::vector<std::vector<float>> r = convert3Dto2D(g);
//
//        t += 0.003;
//        if(t > 360) t = 0;

        std::vector<std::vector<float>> newBasis;

//        for(int i = 0; i < basis.size(); i++){
//            newBasis.push_back(multVecOnMatrix(basis[i], rotateAbs(30)));
//        }

        newBasis = basis;

        std::vector<std::vector<float>> inNewBasis;

        for(int i = 0; i < points.size(); i++){
            inNewBasis.push_back(multVecOnMatrix(points[i], newBasis));
        }

        inNewBasis = convert3Dto2D(inNewBasis);

        window.clear();
        for (int i = 0; i < inNewBasis.size() - 1; i++){
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(inNewBasis[i][0], inNewBasis[i][1])),
                    sf::Vertex(sf::Vector2f(inNewBasis[i + 1][0], inNewBasis[i + 1][1]))
            };
            window.draw(line, 2, sf::Lines);
        }
        window.display();
    }
    return 0;
}