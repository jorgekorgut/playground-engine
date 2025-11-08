#include "InputManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>

bool InputManager::isMenuMode = true;
bool InputManager::firstMouse = true;
float InputManager::lastX     = 0;
float InputManager::lastY     = 0;

void ProcessKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(!InputManager::isMenuMode) {
        return;
    }

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        InputManager::SetMenuMode(false);
    }

    if(key == GLFW_KEY_1 && action == GLFW_PRESS) {
        Engine::GetInstance().renderManager.ToggleWireframeMode();
    }

    if(action == GLFW_PRESS) {
        Engine::GetInstance().inputManager.keysState[key] = true;
    }

    if(action == GLFW_RELEASE) {
        Engine::GetInstance().inputManager.keysState[key] = false;
    }
}

bool InputManager::IsCursorOverImGuiWindow() {
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureMouse;
}

void ProcessMouseButtonInput(GLFWwindow* window, int button, int action, int mods) {
    if(InputManager::IsCursorOverImGuiWindow()) {
        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        return;
    }

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        InputManager::SetMenuMode(true);
    }

    if(action == GLFW_PRESS || action == GLFW_RELEASE) {
        InputManager::MouseButtonEvent mbe =
        InputManager::MouseButtonEvent{ button, action };

        std::vector<std::function<void(InputManager::MouseButtonEvent)>>& mouseButtonCallbacks =
        Engine::GetInstance().inputManager.mouseButtonCallbacks;

        for(const auto& callback : mouseButtonCallbacks) {
            callback(mbe);
        }
    }
}

void ProcessMouseMoveInput(GLFWwindow* window, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

    if(!InputManager::isMenuMode) {
        return;
    }

    float fxpos = (float)xpos;
    float fypos = (float)ypos;

    if(InputManager::firstMouse) {
        InputManager::lastX      = fxpos;
        InputManager::lastY      = fypos;
        InputManager::firstMouse = false;
    }

    float xoffset = fxpos - InputManager::lastX;
    float yoffset = InputManager::lastY - fypos;

    InputManager::lastX = fxpos;
    InputManager::lastY = fypos;

    std::vector<std::function<void(InputManager::MouseMovementEvent)>>& mouseMovementCallbacks =
    Engine::GetInstance().inputManager.mouseMovementCallbacks;
    InputManager::MouseMovementEvent mme =
    InputManager::MouseMovementEvent{ xoffset, yoffset };

    for(const auto& callback : mouseMovementCallbacks) {
        callback(mme);
    }
}

InputManager::InputManager() {
    keysState.resize(1024, false);
}

void InputManager::Initialize() {
    SetMenuMode(true);
    glfwSetKeyCallback((GLFWwindow*)Engine::GetInstance().windowManager.glfwWindow,
    ProcessKeyboardInput);
    glfwSetCursorPosCallback((GLFWwindow*)Engine::GetInstance().windowManager.glfwWindow,
    ProcessMouseMoveInput);
    glfwSetMouseButtonCallback((GLFWwindow*)Engine::GetInstance().windowManager.glfwWindow,
    ProcessMouseButtonInput);
}

void InputManager::Destroy() {
}

void InputManager::SetMenuMode(bool enabled) {
    if(enabled == true && isMenuMode == false) {
        firstMouse = true;
    }

    isMenuMode = enabled;
    if(enabled) {
        glfwSetInputMode((GLFWwindow*)Engine::GetInstance().windowManager.glfwWindow,
        GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode((GLFWwindow*)Engine::GetInstance().windowManager.glfwWindow,
        GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void InputManager::AddMouseMovementCallback(std::function<void(MouseMovementEvent)> callback) {
    mouseMovementCallbacks.push_back(callback);
}

void InputManager::ClearMouseMovementCallback() {
    mouseMovementCallbacks.clear();
}

void InputManager::AddMouseButtonCallback(std::function<void(MouseButtonEvent)> callback) {
    mouseButtonCallbacks.push_back(callback);
}

void InputManager::ClearMouseButtonCallback() {
    mouseButtonCallbacks.clear();
}
