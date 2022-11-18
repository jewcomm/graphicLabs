//
// Created by alexu on 18.11.2022.
//

#include "GraphController.h"

GraphController::GraphController(FigureModel *_model) {
    model = _model;
    newBasis = model->basis;
    buffer = model->points;
}

void GraphController::rotateAbs(bool sign) {
    absAngle += sign ? 0.05 : -0.05;

    float sinFI = sinf(absAngle * M_PI / 180);
    float cosFI = cosf(absAngle * M_PI / 180);
    std::vector<std::vector<float>> r = {{1, 0,         0,     1},
                                         {0, cosFI,     sinFI, 0},
                                         {0, 0 - sinFI, cosFI, 0},
                                         {0, 0,         0,     1}};

    for (auto & i : newBasis) {
        i = multMatrixOnVec(r, i);
    }
    newBasis = inverseMatrix(newBasis);
    for(auto & i: buffer){
        i = multMatrixOnVec(newBasis, i);
    }
}

std::vector<std::vector<float>> GraphController::rotateOrd(float angle){
    float sinFI = sinf(angle * M_PI / 180);
    float cosFI = cosf(angle * M_PI / 180);
    return {
            {cosFI, sinFI, 0, 0},
            {0-sinFI, cosFI, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };
}

std::vector<std::vector<float>> GraphController::rotateApp(float angle){
    float sinFI = sinf(angle * M_PI / 180);
    float cosFI = cosf(angle * M_PI / 180);
    return {
            {cosFI, 0, 0-sinFI, 0},
            {0, 1, 0, 0},
            {sinFI, 0, cosFI, 0},
            {0, 0, 0, 1}
    };
}

std::vector<float> GraphController::multVecOnMatrix(std::vector<float>v, std::vector<std::vector<float>> m){
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

std::vector<float> GraphController::multMatrixOnVec(std::vector<std::vector<float>> m, std::vector<float>v){
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

std::vector<std::vector<float>> GraphController::convert3Dto2D(std::vector<std::vector<float>> input){
    std::vector<std::vector<float>> result;
    for(auto & i : input){
        float mX = model->sizeX / 2 + i[0] * model->dist / (i[3] + model->dist);
        float mY = model->sizeY / 2 + i[1] * model->dist / (i[3] + model->dist);
        result.push_back(std::vector<float>({mX, mY}));
    }
    return result;
}

std::vector<std::vector<float>> GraphController::inverseMatrix(std::vector<std::vector<float>> matrix){
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