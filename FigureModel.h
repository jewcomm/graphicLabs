//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_FIGUREMODEL_H
#define LABA1GRAPHS_FIGUREMODEL_H

#include <vector>
#include <cmath>
#include <iterator>

class FigureModel {
private:
    // enter point in this format, because use traversal from-point-to-point for draw line
    std::vector<std::vector<std::vector<float>>> figureWithoutC = {
        {
            {0,     0,      0},
            {100,   0,      0},
            {100,   0,      100},
            {0,     0,      100}
        },
        {
            {0,     0,      0},
            {0,     100,    0},
            {0,     100,    100},
            {0,     0,      100}
        },
        {
            {0,     0,      100},
            {100,   0,      100},
            {100,   100,    100},
            {0,     100,    100}
        },
        {
            {0,     100,    0},
            {100,   100,    0},
            {100,   100,    100},
            {0,     100,    100}
        },
        {
            {100,   0,      0},
            {100,   100,    0},
            {100,   100,    100},
            {100,   0,      100}
        },
        {
            {0,     0,      0},
            {100,   0,      0},
            {100,   100,    0},
            {0,     100,    0}
        }
    };
//    std::vector<std::vector<float>> figureWithoutC = {
//            //X     Y       Z
//            {100,   0,      0},
//            {100,   100,    0},
//            {0,     100,    0},
//            {0,     0,      0},
//            {100,   0,      0},
//            {0,     0,      0},
//
//            {0,     0,      100},
//            {0,     100,    100},
//            {100,   100,    100},
//            {100,   0,      100},
//            {0,     0,      100},
//            {100,   0,      100},
//
//            {100,   0,      0},
//            {100,   100,    0},
//            {100,   100,    100},
//            {0,     100,    100},
//            {0,     100,    0},
//            {0,     0,      0},
//            {0,     0,      100}
//    };

public:
    struct myLine {
        float p1[3];
        float p2[3];

        inline bool operator==(const myLine& s){
            return (this->p1[0] == s.p1[0] &&
                    this->p1[1] == s.p1[1] &&
                    this->p1[2] == s.p1[2] &&
                    this->p2[0] == s.p2[0] &&
                    this->p2[1] == s.p2[1] &&
                    this->p2[2] == s.p2[2]
                    ||
                    this->p2[0] == s.p1[0] &&
                    this->p2[1] == s.p1[1] &&
                    this->p2[2] == s.p1[2] &&
                    this->p1[0] == s.p2[0] &&
                    this->p1[1] == s.p2[1] &&
                    this->p1[2] == s.p2[2] );
        }
    };



    // with center
//    std::vector<std::vector<float>> figure;
    std::vector<std::vector<std::vector<float>>> figure;

    std::vector<std::vector<myLine>> figureLines;

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
