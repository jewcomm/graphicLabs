//
// Created by alexu on 18.11.2022.
//

#include "FigureModel.h"

FigureModel::FigureModel() {
    float xMax = 0;
    float yMax = 0;
    float zMax = 0;
    // found center our figure
    for(auto & i : figureWithoutC){
        if(i[0] > xMax) xMax = i[0];
        if(i[1] > yMax) yMax = i[1];
        if(i[2] > zMax) zMax = i[2];
    }
    xMax /= 2;
    yMax /= 2;
    zMax /= 2;
    for(auto & i : figureWithoutC){
        figure.push_back(std::vector<float>({i[0] - xMax,
                                            i[1] - yMax,
                                            i[2] - zMax}));
    }
}