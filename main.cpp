#include <vector>
#include "FigureModel.h"
#include "SFMLView.h"

int main()
{
    FigureModel * model = new FigureModel();

    GraphController * controller = new GraphController(model);
    SFMLView view(controller);

    std::vector<std::vector<float>> r1 = {{1, 2, 3},
                                         {4, 5, 6},
                                         {1, 2, 3,}};

    std::vector<std::vector<float>> r2 = {{2, 2, 1},
                                         {4, 8, 7},
                                         {1, 2, 3,}};

    for(auto & i : r1){
        i = controller->multVecOnMatrix(i, r2);
    }


    view.run();

    return 0;
}