//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_GRAPHCONTROLLER_H
#define LABA1GRAPHS_GRAPHCONTROLLER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "FigureModel.h"

#define BASIS_COORD(coord) 500 + (coord - 500) * 100

class GraphController : protected FigureModel {
public:
    GraphController(FigureModel *_model);

    std::vector<std::vector<float>> buffer;
    std::vector<std::vector<float>> newBasis;

    FigureModel *model ;

    std::vector<std::vector<float>> inverseMatrix(std::vector<std::vector<float>> matrix);

    std::vector<std::vector<float>> convert3Dto2D(std::vector<std::vector<float>> input,
                                                  int sizeX, int sizeY, float dist);

    // multiply vector by matrix
    // vector.size() should be less matrix.size()
    std::vector<float> multVecOnMatrix(std::vector<float>v, std::vector<std::vector<float>> m);

    // multiply matrix by vector
    // vector.size() should be less matrix.size()
    std::vector<float> multMatrixOnVec(std::vector<std::vector<float>> m, std::vector<float>v);

    // function for rotate on axel applicate
    void rotateApp(float angle);

    // function for rotate on axel abscissa
    void rotateAbs(float angle);

    // function for rotate on axel ordinate
    void rotateOrd(float angle);

    void comprStret(float a, float b, float c);

    void inverseXOY();

    void inverseYOZ();

    void inverseZOX();

    void transfer(float a, float b, float c);

    inline void reload(){
        newBasis = model->basis;
        buffer = model->figure;
    }
};


#endif //LABA1GRAPHS_GRAPHCONTROLLER_H
