//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_FIGUREMODEL_H
#define LABA1GRAPHS_FIGUREMODEL_H

#include <vector>
#include <cmath>

class FigureModel {
public:
    // enter point in this format, because use traversal from-point-to-point for draw line
    std::vector<std::vector<float>> figure = {
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

    std::vector<std::vector<float>> points;

    // imaginary distance between figure and point (0, 0, 0)
    float dist = 1000;

    float sizeX = 1000;
    float sizeY = 1000;

    float xMax = 0;
    float yMax = 0;
    float zMax = 0;

    float rX = 0;
    float rY = 0;
    float rZ = 0;

    float kX = 1;
    float kY = 1;
    float kZ = 1;

    FigureModel();

// start basis
std::vector<std::vector<float>> basis = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
};
};


#endif //LABA1GRAPHS_FIGUREMODEL_H
