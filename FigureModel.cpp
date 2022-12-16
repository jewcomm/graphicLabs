//
// Created by alexu on 18.11.2022.
//

#include "FigureModel.h"

FigureModel::FigureModel() {
    float xMax = 0;
    float yMax = 0;
    float zMax = 0;
    // found center our figure
    for(auto & j : figureWithoutC){
        for (auto & i  :j) {
            if (i[0] > xMax) xMax = i[0];
            if (i[1] > yMax) yMax = i[1];
            if (i[2] > zMax) zMax = i[2];
        }
    }
    xMax /= 2;
    yMax /= 2;
    zMax /= 2;
//    for(auto & i : figureWithoutC){
//        figure.push_back(std::vector<float>({i[0] - xMax,
//                                            i[1] - yMax,
//                                            i[2] - zMax}));
//    }

    int c = 0;
    for(auto & j : figureWithoutC){
        std::vector<myLine> temp;
        // centered coords
        temp.push_back(myLine{
                {j.back()[0] - xMax,
                 j.back()[1] - yMax,
                 j.back()[2] - zMax},
                {j.front()[0] - xMax,
                 j.front()[1] - yMax,
                 j.front()[2] - zMax},
                 colors[c]
        });

        for (auto & i : j){
            if(i == j.back()) break;
            auto next = std::next(&i, 1);
            temp.push_back(myLine{
                {
                    i[0] - xMax,
                    i[1] - yMax,
                    i[2] - zMax
                },
                {(*next)[0] - xMax,
                    (*next)[1] - yMax,
                    (*next)[2] - zMax
                },
                colors[c]});
        }

        figureLines.push_back(temp);
        c++;
    }
}