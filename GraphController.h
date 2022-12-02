//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_GRAPHCONTROLLER_H
#define LABA1GRAPHS_GRAPHCONTROLLER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "FigureModel.h"
#include <algorithm>

#define BASIS_COORD(coord) 500 + (coord - 500) * 100
#define X3D_TO_X2D(x, z, sizeX, dist) sizeX / 2 + x * dist / (z + dist)
#define Y3D_TO_X2D(y, z, sizeY, dist) sizeY / 2 + y * dist / (z + dist)


class GraphController : FigureModel {
public:
    explicit GraphController(FigureModel *_model);

    FigureModel *model;

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

    std::vector<std::vector<FigureModel::myLine>> linesWithDuplicate;
    std::vector<FigureModel::myLine> clearLines;
    std::vector<std::vector<float>> outputBuffer;
    std::vector<std::vector<float>> newBasis;

    __attribute__((unused)) std::vector<std::vector<float>> inverseMatrix(std::vector<std::vector<float>> matrix);

    std::vector<std::vector<float>> convert3Dto2D(std::vector<std::vector<float>> input,
                                                  int sizeX, int sizeY, float dist);

    std::vector<float> convert3Dto2D(std::vector<float> input,
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
        linesWithDuplicate = model->figureLines;
    }

    inline void clear(){
        angleX = angleY = angleZ = 0;
        dilationX = dilationY = dilationZ = 1;
        transfX = transfY = transfZ = 0;
        invZOX = invYOZ = invXOY = false;
    }

    inline void zBufferToOutputBuffer(){
        std::vector<FigureModel::myLine> tempLines;
        // магию надо делать тут
        for(auto & j: linesWithDuplicate) {
            for(auto & i : j){
                auto f = std::find(tempLines.begin(), tempLines.end(), i);
                if(f == tempLines.end()) tempLines.push_back(i);
            }
        }
        clearLines = tempLines;
    }

    std::vector<std::vector<sf::Vertex>> calcPhysics(float sizeX, float sizeY, float dist);
};


#endif //LABA1GRAPHS_GRAPHCONTROLLER_H
