#pragma once
#include "scene/SceneManager.h"
#include "shader/Shader.h"
#include "window/WindowManager.h"
#include <glm/vec4.hpp>
#include "ecs/System.h"

class RenderManager : public System {
    public:
    RenderManager();
    void Initialize();
    void Destroy();
    void Clear();
    void ToggleWireframeMode();
    void Render(WindowManager& windowManager, SceneManager& sceneManager);
    Shader shader;

    private:
    glm::vec4 clearColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
    bool wireframeMode   = false;
};
