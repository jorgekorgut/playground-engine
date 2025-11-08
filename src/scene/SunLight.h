#pragma once
#include "Transform.h"
#include <glm/vec3.hpp>

class SunLight {
    public:
    SunLight() {
    }
    virtual ~SunLight() {
    }
    Transform transform;
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
};
