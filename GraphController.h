//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_GRAPHCONTROLLER_H
#define LABA1GRAPHS_GRAPHCONTROLLER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "FigureModel.h"

#define BASIS_COORD(coord) 500 + (coord - 500) * 100

class GraphController {
public:
    explicit GraphController(FigureModel *_model);

    float angleZ = 0;
    float angleX = 0;
    float angleY = 0;

    float dilationX = 1;
    float dilationY = 1;
    float dilationZ = 1;

    float transfX = 0;
    float transfY = 0;
    float transfZ = 0;

    bool invXOY = false;
    bool invYOZ = false;
    bool invZOX = false;

    std::vector<std::vector<float>> buffer;
    std::vector<std::vector<float>> newBasis;

    FigureModel *model ;

    __attribute__((unused)) std::vector<std::vector<float>> inverseMatrix(std::vector<std::vector<float>> matrix);

    std::vector<std::vector<float>> convert3Dto2D(std::vector<std::vector<float>> input,
                                                  int sizeX, int sizeY, float dist);

    // multiply vector by matrix
    // vector.size() should be less matrix.size()
    std::vector<float> multVecOnMatrix(std::vector<float>v, std::vector<std::vector<float>> m);

    // multiply matrix by vector
    // vector.size() should be less matrix.size()
    __attribute__((unused)) std::vector<float> multMatrixOnVec(std::vector<std::vector<float>> m, std::vector<float>v);

    // function for rotate on axel applicate
    void rotateApp();

    // function for rotate on axel abscissa
    void rotateAbs();

    // function for rotate on axel ordinate
    void rotateOrd();

    void comprStret();

    void inverseXOY();

    void inverseYOZ();

    void inverseZOX();

    void transfer();

    inline void reload(){
        newBasis = model->basis;
        buffer = model->figure;
    }

    inline void clear(){
        angleX = angleY = angleZ = 0;
        dilationX = dilationY = dilationZ = 1;
        transfX = transfY = transfZ = 0;
        invZOX = invYOZ = invXOY = false;
    }

    std::vector<std::vector<float>> calcPhysics();
};


#endif //LABA1GRAPHS_GRAPHCONTROLLER_H
