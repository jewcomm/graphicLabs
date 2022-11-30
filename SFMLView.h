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
    SFMLView(GraphController *controller);
    int run();

private:
};


#endif //LABA1GRAPHS_SFMLVIEW_H
