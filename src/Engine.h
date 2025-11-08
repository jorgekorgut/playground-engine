#pragma once

#include "input/InputManager.h"
#include "render/RenderManager.h"
#include "scene/SceneManager.h"
#include "window/WindowManager.h"
#include <ecs/ComponentManager.h>
#include <ecs/EntityManager.h>
#include <ecs/SystemManager.h>
#include <imgui/ImGuiManager.h>

class ScriptableObject;
class GameObject;

class Engine {
    public:
    Engine(Engine& other)         = delete;
    void operator=(const Engine&) = delete;
    static Engine& GetInstance();

    void Initialize();
    void Destroy();
    void StartLoop();

    void AddScriptableObject(ScriptableObject* object);
    void RemoveScriptableObject(ScriptableObject* object);

    WindowManager windowManager;
    InputManager inputManager;
    ImGuiManager imguiManager;
    SceneManager sceneManager;
    RenderManager renderManager;
    SystemManager systemManager;

    EntityManager entityManager;
    ComponentManager componentManager;

    float deltaTime = 0.0f; // Time between current frame and last frame

    private:
    Engine() {
    }

    std::vector<ScriptableObject*> scriptsList;
    float lastFrame = 0.0f; // Time of last frame
    static Engine* instance;
};
