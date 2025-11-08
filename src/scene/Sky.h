#pragma once
#include <shader/Shader.h>
#include <memory>
#include "SunLight.h"
#include "Mesh.h"
#include "ModelSky.h"
#include "resource/ResourceManager.h"

class Sky {
    public:
    Sky() {
        shader = ResourceManager::LoadShader(
        "engine_shaders/SkyShader.vert", "engine_shaders/SkyShader.frag");
        sunLight.transform.position = glm::vec3(50.0f, 100.0f, 0.0f);
    }

    virtual ~Sky() {
    }

    ModelSky model;
    Shader shader;
    SunLight sunLight;
};
