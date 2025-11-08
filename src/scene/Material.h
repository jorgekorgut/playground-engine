#pragma once
#include <glm/vec3.hpp>

class Material {
    public:
    Material(glm::vec3& color = glm::vec3(1));
    glm::vec3 color;
};
