//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_GRAPHCONTROLLER_H
#define LABA1GRAPHS_GRAPHCONTROLLER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "FigureModel.h"

class GraphController {
    float absAngle = 0;


public:
    GraphController(FigureModel *_model);
    FigureModel *model ;

    std::vector<std::vector<float>> buffer;
    std::vector<std::vector<float>> newBasis;

    std::vector<std::vector<float>> inverseMatrix(std::vector<std::vector<float>> matrix);

    std::vector<std::vector<float>> convert3Dto2D(std::vector<std::vector<float>> input);

    // multiply vector by matrix
    // vector.size() should be less matrix.size()
    std::vector<float> multVecOnMatrix(std::vector<float>v, std::vector<std::vector<float>> m);

    // multiply matrix by vector
    // vector.size() should be less matrix.size()
    std::vector<float> multMatrixOnVec(std::vector<std::vector<float>> m, std::vector<float>v);

    // function for rotate on axel applicate
    std::vector<std::vector<float>> rotateApp(float angle);

    // function for rotate on axel abscissa
    void rotateAbs(bool sign);

    // function for rotate on axel ordinate
    std::vector<std::vector<float>> rotateOrd(float angle);

    inline void newBasisClear(){
        newBasis = model->basis;
    }
};


#endif //LABA1GRAPHS_GRAPHCONTROLLER_H
