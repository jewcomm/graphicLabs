//
// Created by alexu on 18.11.2022.
//

#include "FigureModel.h"

FigureModel::FigureModel() {
    // found center our figure
    float xMax = 0;
    float yMax = 0;
    float zMax = 0;
    for(auto & i : figure){
        if(i[0] > xMax) xMax = i[0];
        if(i[1] > yMax) yMax = i[1];
        if(i[2] > zMax) zMax = i[2];
    }
    xMax /= 2;
    yMax /= 2;
    zMax /= 2;
    for(auto & i : figure){
        points.push_back(std::vector<float>({i[0] - xMax,
                                            i[1] - yMax,
                                            i[2] - zMax}));
    }
}