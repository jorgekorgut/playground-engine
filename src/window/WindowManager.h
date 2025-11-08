#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
    public:
    WindowManager();
    void Destroy();

    GLFWwindow* window = nullptr;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    int windowWidth  = 800;
    int windowHeight = 600;

    private:
    const char* windowTitle = "Engine";
};
