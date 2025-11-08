#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

class InputManager {
    public:
    struct MouseMovementEvent {
        float x;
        float y;
    };

    struct KeyEvent {
        int key;
    };

    struct MouseButtonEvent {
        int button;
        int action;
    };

    static void ProcessMouseMoveInput(GLFWwindow* window, double xpos, double ypos);
    static void ProcessMouseButtonInput(GLFWwindow* window, int button, int action, int mods);
    static void
    ProcessKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    static bool IsCursorOverImGuiWindow();
    static void SetMenuMode(bool enabled);

    InputManager();
    void Initialize();
    void Destroy();
    void AddMouseMovementCallback(std::function<void(MouseMovementEvent)> callback);
    void ClearMouseMovementCallback();
    void AddMouseButtonCallback(std::function<void(MouseButtonEvent)> callback);
    void ClearMouseButtonCallback();

    std::vector<bool> keysState;

    private:
    static bool isMenuMode;
    static float lastX;
    static float lastY;
    static bool firstMouse;

    std::vector<std::function<void(MouseMovementEvent)>> mouseMovementCallbacks;
    std::vector<std::function<void(MouseButtonEvent)>> mouseButtonCallbacks;
};
