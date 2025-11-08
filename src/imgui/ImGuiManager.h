#pragma once
#include <memory>
#include <vector>
#include "ecs/System.h"

class ImGuiManager : public System {
    public:
    void Initialize();
    void Destroy();
    void RenderUIData();
    void NewFrame();
    void Render();

    static void SliderFloat(const char* label, float* value, float min, float max);
};
