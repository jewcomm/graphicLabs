#include "GraphController.h"
#include <SFML/Graphics.hpp>
#include <cmath>

GraphController::GraphController(FigureModel *_model) {
    model = _model;
    reload();
}

void GraphController::rotateAbs() {
    if(std::fabs(angleX) > 360) angleX = fmod(angleX , 360);

    auto sinFI = sinf(angleX * M_PI / 180);
    float cosFI = cosf(angleX * M_PI / 180);
    std::vector<std::vector<float>> r = {{1, 0,         0,     0},
                                         {0, cosFI,     sinFI, 0},
                                         {0, 0 - sinFI, cosFI, 0},
                                         {0, 0,         0,     1}};

    for (auto & i : newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

void GraphController::rotateApp(){
    if(fabs(angleZ) > 360) angleZ = fmod(angleZ , 360.0);

    float sinFI = sinf(angleZ * M_PI / 180);
    float cosFI = cosf(angleZ * M_PI / 180);
    std::vector<std::vector<float>> r = {{cosFI, sinFI, 0, 0},
                                        {0-sinFI, cosFI, 0, 0},
                                        {0, 0, 1, 0},
                                        {0, 0, 0, 1}};

    for (auto & i : newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

void GraphController::rotateOrd(){
    if(abs(angleY) > 360) angleY = fmod(angleY , 360);

    float sinFI = sinf(angleY * M_PI / 180);
    float cosFI = cosf(angleY * M_PI / 180);
    std::vector<std::vector<float>> r = {{cosFI, 0, 0-sinFI, 0},
                                        {0, 1, 0, 0},
                                        {sinFI, 0, cosFI, 0},
                                        {0, 0, 0, 1}};

    for (auto & i : newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

void GraphController::comprStret() {
    std::vector<std::vector<float>> r = {{dilationX, 0, 0, 0},
                                         {0, dilationY, 0, 0},
                                         {0, 0, dilationZ, 0},
                                         {0, 0, 0, 1}};

    for (auto & i: newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

void GraphController::inverseXOY() {
    std::vector<std::vector<float>> r = {{1, 0, 0, 0},
                                         {0, 1, 0, 0},
                                         {0, 0, 0-1, 0},
                                         {0, 0, 0, 1}};

    for (auto & i : newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

void GraphController::inverseYOZ() {
    std::vector<std::vector<float>> r = {{0-1, 0, 0, 0},
                                         {0, 1, 0, 0},
                                         {0, 0, 1, 0},
                                         {0, 0, 0, 1}};

    for (auto & i : newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

void GraphController::inverseZOX() {
    std::vector<std::vector<float>> r = {{1, 0, 0, 0},
                                         {0, 0-1, 0, 0},
                                         {0, 0, 1, 0},
                                         {0, 0, 0, 1}};

    for (auto & i : newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

void GraphController::transfer() {
    std::vector<std::vector<float>> r = {{1, 0, 0, 0},
                                         {0, 1, 0, 0},
                                         {0, 0, 1, 0},
                                         {transfX, transfY, transfZ, 1}};

    for (auto & i : newBasis) {
        i = multVecOnMatrix(i, r);
    }
}

std::vector<float> GraphController::multVecOnMatrix(std::vector<float>v, std::vector<std::vector<float>> m){
    std::vector<float> res;
    int count = 0;
    while(v.size() < m.size()){
        v.push_back(1);
        count++;
    }

    for(int i =0; i < v.size(); i++){
        float t = 0;
        for(int j = 0; j < m.size(); j++){
            t += v[j] * m[j][i];
        }
        res.push_back(t);
    }

    while(count--){
        res.pop_back();
    }
    return res;
}

__attribute__((unused)) std::vector<float> GraphController::multMatrixOnVec(std::vector<std::vector<float>> m, std::vector<float>v){
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

std::vector<std::vector<float>> GraphController::convert3Dto2D(std::vector<std::vector<float>> input, float sizeX, float sizeY, float dist){
    std::vector<std::vector<float>> result;
    for(auto & i : input){
        float mX = (float)sizeX / 4 + i[0] * dist / (i[2] + dist);
        float mY = (float)sizeY / 2 + i[1] * dist / (i[2] + dist);
        result.push_back(std::vector<float>({mX, mY, i[2]}));
    }
    return result;
}

std::vector<float> GraphController::convert3Dto2D(std::vector<float> input, float sizeX, float sizeY, float dist){
        float mX = (float)sizeX / 2 + input[0] * dist / (input[2] + dist);
        float mY = (float)sizeY / 2 + input[1] * dist / (input[2] + dist);
        std::vector<float> result({mX, mY, input[2]});
        return result;
}

__attribute__((unused)) std::vector<std::vector<float>> GraphController::inverseMatrix(std::vector<std::vector<float>> matrix){
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

__attribute__((unused)) std::vector<std::vector<sf::Vertex>> GraphController::calcPhysics(float sizeX, float sizeY, float dist) {
    std::vector<std::vector<sf::Vertex>> result;
    reload();
    rotateApp();
    rotateOrd();
    rotateAbs();
    comprStret();
    transfer();
    if(invXOY) inverseXOY();
    if(invYOZ) inverseYOZ();
    if(invZOX) inverseZOX();

    get3dWithDepth(sizeX, sizeY, dist);

    clearDuplicates();

    for(auto & i : clearLines ){
        std::vector<float> p1 = std::vector<float>({i.p1[0], i.p1[1], i.p1[2]});
        std::vector<float> p2 = std::vector<float>({i.p2[0], i.p2[1], i.p2[2]});
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(p1[0], p1[1])),
                sf::Vertex(sf::Vector2f(p2[0], p2[1]))

        };
        std::vector<sf::Vertex> t = {line[0], line[1]};
        result.push_back(t);
    }
    return result;
}

std::vector<sf::ConvexShape> GraphController::calcPhysiscPoligon(float sizeX, float sizeY, float dist) {
    std::vector<sf::ConvexShape> result;
    reload();
    rotateApp();
    rotateOrd();
    rotateAbs();
    comprStret();
    transfer();
    if(invXOY) inverseXOY();
    if(invYOZ) inverseYOZ();
    if(invZOX) inverseZOX();

    get3dWithDepth(sizeX, sizeY, dist);

    std::vector<std::pair<std::vector<myLine>, float>> polWithDepthSum;

    for(auto & i : linesWithDuplicate) {
        float sum = 0;
        for(auto & j : i){
            sum += j.p1[2];
        }
        auto t = std::make_pair(i, sum);
        polWithDepthSum.push_back(t);
    }

    std::sort(polWithDepthSum.begin(), polWithDepthSum.end(), [](auto &left, auto &right){
       return left.second > right.second;
    });

    int t = 0;
    for(auto & i : polWithDepthSum) {
        sf::ConvexShape convex;
        convex.setPointCount(i.first.size());
        for(int j = 0; j < i.first.size(); j++){
            convex.setPoint(j, sf::Vector2f(i.first[j].p1[0], i.first[j].p1[1]));
        }
        convex.setFillColor(i.first[0].color);
        result.push_back(convex);
        t++;
    }

//    for(auto & i : linesWithDuplicate) {
//        sf::ConvexShape convex;
//        convex.setPointCount(i.size());
//        for(int j = 0; j < i.size(); j++){
//            convex.setPoint(j, sf::Vector2f(i[j].p1[0], i[j].p1[1]));
//        }
//        convex.setFillColor(colors[t]);
//        result.push_back(convex);
//        t++;
//    }

    return result;
}