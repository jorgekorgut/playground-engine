#pragma once

class WindowManager {
    public:
    WindowManager();
    void Destroy();

    void* glfwWindow = nullptr;

    int windowWidth  = 800;
    int windowHeight = 600;

    private:
    const char* windowTitle = "Engine";
};
