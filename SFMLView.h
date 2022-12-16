//
// Created by alexu on 18.11.2022.
//

#ifndef LABA1GRAPHS_SFMLVIEW_H
#define LABA1GRAPHS_SFMLVIEW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "FigureModel.h"
#include "GraphController.h"

class SFMLView {
public:
    GraphController *controller;
    explicit SFMLView(GraphController *controller);
    int run();

    int sizeX = 1600;
    int sizeY = 1000;

    // imaginary distance between figure and point (0, 0, 0)
    float dist = 10000;

private:
};


#endif //LABA1GRAPHS_SFMLVIEW_H
