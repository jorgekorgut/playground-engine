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
    const char* vertexPath   = "engine_shaders/DefaultShader.vert",
    const char* fragmentPath = "engine_shaders/DefaultShader.frag");

    static Texture LoadTexture(const std::string& vertexPath);

    static Texture LoadCubemap(std::vector<std::string> faces, const std::string directory);
};
