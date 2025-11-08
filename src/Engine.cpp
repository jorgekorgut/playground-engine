#include "Engine.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input/InputManager.h"
#include "window/WindowManager.h"
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

    imguiManager.Initialize();
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

    GLFWwindow* window = (GLFWwindow*)windowManager.glfwWindow;
    while(!glfwWindowShouldClose(window)) {
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

        glfwSwapBuffers(window);
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
