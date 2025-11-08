#include "Engine.h"
#include "input/InputManager.h"
#include "window/WindowManager.h"
#include <imgui.h>
#include <imgui/UIObject.h>
#include <imgui/ImGuiManager.h>
#include <scene/Material.h>
#include <scene/GameObject.h>
#include <scripts/ScriptableObject.h>

Engine& Engine::GetInstance() {
    static Engine instance;
    return instance;
}

void Engine::Initialize() {
    componentManager.RegisterComponent<Transform>();
    componentManager.RegisterComponent<Model>();
    componentManager.RegisterComponent<Material>();
    componentManager.RegisterComponent<UIObject>();

    imguiManager.Initialize(windowManager.window);
    inputManager.Initialize();

    renderManager.Initialize();
}

void Engine::Destroy() {
    imguiManager.Destroy();
}

void Engine::StartLoop() {
    for(ScriptableObject* currentScript : scriptsList) {
        currentScript->Start();
    }

    while(!glfwWindowShouldClose(windowManager.window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime          = currentFrame - lastFrame;
        lastFrame          = currentFrame;

        for(ScriptableObject* currentScript : scriptsList) {
            currentScript->Update();
        }

        renderManager.Clear();

        imguiManager.NewFrame();

        renderManager.Render(windowManager, sceneManager);

        imguiManager.RenderUIData();

        imguiManager.Render();

        glfwSwapBuffers(windowManager.window);
        glfwPollEvents();
    }
}

void Engine::AddScriptableObject(ScriptableObject* object) {
    scriptsList.push_back(object);
}

void Engine::RemoveScriptableObject(ScriptableObject* object) {
    scriptsList.erase(std::remove(scriptsList.begin(), scriptsList.end(), object),
    scriptsList.end());
}
