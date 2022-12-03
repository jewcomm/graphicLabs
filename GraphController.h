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

#define BASIS_COORD(coord, size) size / 2 + (coord - size / 2) * 100
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

    bool showBorder = false;

    std::vector<std::vector<uint8_t>> ZBuffer;
    size_t zBufferXSize;
    size_t zBufferYSize;

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
                i.p2[0] = p2[0];
                i.p2[1] = p2[1];
            }
        }

        float maxX = 0;
        float minX = sizeX;

        float maxY = 0;
        float minY = sizeY;

        float maxZ = 0;
        float minZ = 1000000;

        for(auto & j : linesWithDuplicate) {
            for(auto & i: j){
                if(i.p1[0] > maxX) maxX = i.p1[0];
                if(i.p1[1] > maxY) maxY = i.p1[1];
                if(i.p2[0] > maxX) maxX = i.p2[0];
                if(i.p2[1] > maxY) maxY = i.p1[1];
                if(i.p1[2] > maxZ) maxZ = i.p1[2];
                if(i.p2[2] > maxZ) maxZ = i.p2[2];

                if(i.p1[0] < minX) minX = i.p1[0];
                if(i.p1[1] < minY) minY = i.p1[1];
                if(i.p2[0] < minX) minX = i.p2[0];
                if(i.p2[1] < minY) minY = i.p1[1];
                if(i.p1[2] < minZ) minZ = i.p1[2];
                if(i.p2[2] < minZ) minZ = i.p2[2];
            }
        }

        if(showBorder) {
            std::vector<myLine> border = {
                    {
                            {maxX, maxY, 0},
                            {maxX, minY, 0}
                    },
                    {
                            {maxX, minY, 0},
                            {minX, minY, 0}
                    },
                    {
                            {minX, minY, 0},
                            {minX, maxY, 0}
                    },
                    {
                            {minX, maxY, 0},
                            {maxX, maxY, 0}
                    }
            };
            linesWithDuplicate.push_back(border);
        }

        std::vector<std::vector<uint8_t>> zBuffer;
        int ySizeBuffer = ceil(maxY) - floor(minY);
        int xSizeBuffer = ceil(maxX) - floor(minX);
        for(int i = 0; i <= ySizeBuffer; i++){
            std::vector<uint8_t> t;
            t.resize(xSizeBuffer + 1);
            t[10] = 1;
            t[11] = 1;
            zBuffer.push_back(t);
        }
        float zRange = maxZ - minZ;
        float ZStep = zRange / UINT8_MAX;


        ZBuffer = zBuffer;
        zBufferXSize = xSizeBuffer;
        zBufferYSize = ySizeBuffer;
    }

    std::vector<std::vector<sf::Vertex>> calcPhysics(float sizeX, float sizeY, float dist);
};


#endif //LABA1GRAPHS_GRAPHCONTROLLER_H
