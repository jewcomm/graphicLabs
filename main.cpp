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
        for(int j = 0; j < v.size(); j++){
            temp += m[i][j] * v[j];
        }
        res.push_back(temp);
    }
    v.pop_back();
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

    /*
    std::vector<std::vector<float>> aftR1;
    for(int i = 0; i < points.size(); i++){
        std::vector<float> res = mult(points[i], rotate);
        //std::vector<float> res = mult(std::vector<float>({3,2,1}), points);
        aftR1.push_back(res);
    }

    std::vector<std::vector<float>> aftR2;
    for(int i = 0; i < aftR1.size(); i++){
        std::vector<float> res = mult(aftR1[i], rabs);
        //std::vector<float> res = mult(std::vector<float>({3,2,1}), points);
        aftR2.push_back(res);
    }

    std::vector<std::vector<float>> aftR;
    for(int i = 0; i < aftR2.size(); i++){
        std::vector<float> res = mult(aftR2[i], rabsciss);
        //std::vector<float> res = mult(std::vector<float>({3,2,1}), points);
        aftR.push_back(res);
    }

    */
//    for(int i = 0; i < points.size(); i++){
//        std::vector<float> t;
//        float x = aftR[i][0];
//        float y = aftR[i][1];
//        float z = aftR[i][2];
//        float mX = sizeX / 2 + x * dist / (z + dist);
//        float mY = sizeY / 2 - y * dist / (z + dist);
//        t.push_back(mX);
//        t.push_back(mY);
//        pointInNewCoord.push_back(t);
//    }

    float t = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::vector<std::vector<float>> f;

        for(int i = 0; i < points.size(); i++){
            f.push_back(multVecOnMatrix(points[i], rotateApp(t)));
        }

        std::vector<std::vector<float>> k;

        for(int i = 0; i < f.size(); i++){
            k.push_back(multVecOnMatrix(f[i], rotateAbs(t)));
        }

        std::vector<std::vector<float>> g;

        for(int i = 0; i < k.size(); i++){
            g.push_back(multVecOnMatrix(k[i], rotateOrd(t)));
        }

        std::vector<std::vector<float>> r = convert3Dto2D(g);

        t += 0.003;
        if(t > 360) t = 0;

        window.clear();
        for (int i = 0; i < r.size() - 1; i++){
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(r[i][0], r[i][1])),
                    sf::Vertex(sf::Vector2f(r[i + 1][0], r[i + 1][1]))
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