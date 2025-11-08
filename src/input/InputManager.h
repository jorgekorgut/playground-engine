#pragma once

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

    static bool IsCursorOverImGuiWindow();
    static void SetMenuMode(bool enabled);

    InputManager();
    void Initialize();
    void Destroy();
    void AddMouseMovementCallback(std::function<void(MouseMovementEvent)> callback);
    void ClearMouseMovementCallback();
    void AddMouseButtonCallback(std::function<void(MouseButtonEvent)> callback);
    void ClearMouseButtonCallback();

    std::vector<std::function<void(MouseMovementEvent)>> mouseMovementCallbacks;
    std::vector<std::function<void(MouseButtonEvent)>> mouseButtonCallbacks;
    std::vector<bool> keysState;
    static bool isMenuMode;
    static float lastX;
    static float lastY;
    static bool firstMouse;
};
