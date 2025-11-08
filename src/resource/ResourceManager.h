#pragma once
#include <shader/Shader.h>
#include "Texture.h"
#include <vector>
#include <string>

class ResourceManager {
    public:
    void Initialize();
    void Destroy();
    static Shader LoadShader(
    const char* vertexPath   = "shaders/DefaultShader.vert",
    const char* fragmentPath = "shaders/DefaultShader.frag");

    static Texture LoadTexture(const std::string& vertexPath);

    static Texture LoadCubemap(std::vector<std::string> faces, const std::string directory);
};
