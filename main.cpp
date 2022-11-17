#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// enter point in this format, because use traversal from-point-to-point for draw line
const std::vector<std::vector<float>> points = {
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

// start basis
const std::vector<std::vector<float>> basis = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
};

// size window
float sizeX = 1000;
float sizeY = 1000;

// imaginary distance between figure and point (0, 0, 0)
float dist = 1000;

// function for rotate on axel abscissa
std::vector<std::vector<float>> rotateAbs(float angle){
    float sinFI = sinf(angle * M_PI / 180);
    float cosFI = cosf(angle * M_PI / 180);
    return {{1, 0, 0, 1},
            {0, cosFI, sinFI, 0},
            {0, 0-sinFI, cosFI, 0},
            {0, 0, 0, 1}};
}

// function for rotate on axel ordinate
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

// function for rotate on axel applicate
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

// multiply vector by matrix
// vector.size() should be less matrix.size()
std::vector<float> multVecOnMatrix(std::vector<float>v, std::vector<std::vector<float>> m){
    std::vector<float> res;
    int count = 0;
    while(v.size() < m.size()){
        v.push_back(1);
        count++;
    }
    for(int i = 0; i < m.size(); i++){
        float temp = 0;
        for(int j = 0; j < m.size(); j++){
            temp += m[i][j] * v[j];
        }
        res.push_back(temp);
    }
    while(count--){
        res.pop_back();
    }
    return res;
}

// multiply matrix by vector
// vector.size() should be less matrix.size()
std::vector<float> multMatrixOnVec(std::vector<std::vector<float>> m, std::vector<float>v){
    std::vector<float> res;
    int count = 0;
    while(v.size() < m.size()){
        v.push_back(1);
        count++;
    }
    for(int i = 0; i < m.size(); i++){
        float temp = 0;
        for(int j = 0; j < m.size(); j++){
            temp += m[j][i] * v[j];
        }
        res.push_back(temp);
    }
    while(count--){
        res.pop_back();
    }
    return res;
}

// convert vector3 to vector2 with depth
std::vector<std::vector<float>> convert3Dto2D(std::vector<std::vector<float>> input){
    std::vector<std::vector<float>> result;
    for(auto & i : input){
        float mX = sizeX / 2 + i[0] * dist / (i[3] + dist);
        float mY = sizeY / 2 + i[1] * dist / (i[3] + dist);
        result.push_back(std::vector<float>({mX, mY}));
    }
    return result;
}

std::vector<std::vector<float>> inverseMatrix(std::vector<std::vector<float>> matrix){
    sf::Transform source(matrix[0][0], matrix[0][1], matrix[0][2],
                         matrix[1][0], matrix[1][1], matrix[1][2],
                         matrix[2][0], matrix[2][1], matrix[2][2]);

    sf::Transform inverse = source.getInverse();
    auto *r = inverse.getMatrix();
    std::vector<float> revers(r, r+16);

    std::vector<std::vector<float>> ret;

    /*
     * Transform insert line and row with only 1 between second and third line/row
     * 1 1 1        \       1 1 0 1
     * 2 2 2    ------      2 2 0 2
     * 3 3 3        /       0 0 1 0
     *                      3 3 0 3
     *
     * after inverse need delete this line and row
     */
    for(int i = 0; i < 4; i++){
        if(i == 2) continue;
        std::vector<float> temp;
        for(int j = 0; j < 4; j++){
            if(j != 2) temp.push_back(revers[i * 4 + j]);
        }
        ret.push_back(temp);
    }

    return ret;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "Lab's 1 graphic affine processing");

    window.setFramerateLimit(60);

    float t = 0;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // new basis for transform figure
        std::vector<std::vector<float>> newBasis;
        // add new coordinates new basis
        for(auto & i : basis){
            newBasis.push_back(multMatrixOnVec(rotateAbs(t), i));
        }

        // inverse matrix
        std::vector<std::vector<float>> inverseNewBasis = inverseMatrix(newBasis);

        // coordinates in new basis
        std::vector<std::vector<float>> inNewBasis;
        for(auto & point : points){
            inNewBasis.push_back(multMatrixOnVec(inverseNewBasis, point));
        }

        // transform vector3 to vector2
        inNewBasis = convert3Dto2D(inNewBasis);

        // increment for testng :)
        t += 0.03;

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