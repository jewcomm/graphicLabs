#include <vector>
#include "FigureModel.h"
#include "SFMLView.h"

int main()
{
    FigureModel * model = new FigureModel();
    GraphController * controller = new GraphController(model);
    SFMLView view(controller);

    view.run();

    return 0;
}