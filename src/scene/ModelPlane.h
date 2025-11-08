#pragma once
#include "Model.h"

class ModelPlane : public Model {
    public:
    ModelPlane(int numCol = 1, int numRow = 1);

    int numCol;
    int numRow;
};
