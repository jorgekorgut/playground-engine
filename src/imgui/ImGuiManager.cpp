#include "ImGuiManager.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <string>
#include <Engine.h>
#include "UIObject.h"
#include "ecs/SystemManager.h"


void ImGuiManager::Initialize(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    Signature signature;
    signature.set(Engine::GetInstance().componentManager.GetComponentType<UIObject>());
    Engine::GetInstance().systemManager.RegisterSystem<ImGuiManager>(this, signature);
}

void ImGuiManager::Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::RenderUIData() {
    ImGui::Begin("Properties");
    std::string fps("FPS: ");
    fps += std::to_string((int)ImGui::GetIO().Framerate);
    ImGui::Text(fps.c_str());

    for(const Entity& currentEntity : mEntities) {
        UIObject uiObject =
        Engine::GetInstance().componentManager.GetComponent<UIObject>(currentEntity);

        if(uiObject.callback != nullptr) {
            uiObject.callback();
        }
    }

    ImGui::End();
}

void ImGuiManager::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
