#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <memory>
#include <vector>
#include "ecs/System.h"

class ImGuiManager : public System {
    public:
    void Initialize(GLFWwindow* window);
    void Destroy();

    void RenderUIData();
    void NewFrame();
    void Render();
};
