//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_FIGUREMODEL_H
#define LABA1GRAPHS_FIGUREMODEL_H

#include <vector>
#include <cmath>

class FigureModel {
private:
    // enter point in this format, because use traversal from-point-to-point for draw line
    std::vector<std::vector<float>> figureWithoutC = {
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

public:
    // with center
    std::vector<std::vector<float>> figure;

    FigureModel();

    // start basis
    std::vector<std::vector<float>> basis = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
    };
};


#endif //LABA1GRAPHS_FIGUREMODEL_H
