//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_GRAPHCONTROLLER_H
#define LABA1GRAPHS_GRAPHCONTROLLER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "FigureModel.h"
#include <algorithm>
#include <limits>
#include <map>

#define BASIS_COORD(coord, size) size / 2 + (coord - size / 2) * 100


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
                                                  float sizeX, float sizeY, float dist);

    std::vector<float> convert3Dto2D(std::vector<float> input,
                                     float sizeX, float sizeY, float dist);

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

    inline void clearDuplicates(){
        std::vector<FigureModel::myLine> tempLines;
        for(auto & j: linesWithDuplicate) {
            for(auto & i : j){
                auto f = std::find(tempLines.begin(), tempLines.end(), i);
                if(f == tempLines.end()) tempLines.push_back(i);
            }
        }
        clearLines = tempLines;
    }

    inline void get3dWithDepth(float sizeX, float sizeY, float dist){
        for(auto & j : linesWithDuplicate) {
            for(auto & i: j) {
                std::vector<float> p1 = multVecOnMatrix(std::vector<float>({i.p1[0], i.p1[1], i.p1[2]}), newBasis);
                std::vector<float> p2 = multVecOnMatrix(std::vector<float>({i.p2[0], i.p2[1], i.p2[2]}), newBasis);
                p1 = convert3Dto2D(p1, sizeX, sizeY, dist);
                p2 = convert3Dto2D(p2, sizeX, sizeY, dist);
                i.p1[0] = p1[0];
                i.p1[1] = p1[1];
                i.p1[2] = p1[2];
                i.p2[0] = p2[0];
                i.p2[1] = p2[1];
                i.p2[2] = p2[2];
            }
        }
    }

    __attribute__((unused)) std::vector<std::vector<sf::Vertex>> calcPhysics(float sizeX, float sizeY, float dist);

    std::vector<sf::ConvexShape> calcPhysiscPoligon(float sizeX, float sizeY, float dist);
};


#endif //LABA1GRAPHS_GRAPHCONTROLLER_H
