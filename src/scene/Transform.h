#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>

class Transform {
    public:
    Transform(std::shared_ptr<Transform> parent = nullptr,
    glm::vec3& position                         = glm::vec3(0),
    glm::vec3& rotation                         = glm::vec3(0),
    glm::vec3& scale                            = glm::vec3(1));

    glm::mat4 GetModelMatrix() const;

    std::shared_ptr<Transform> parent = nullptr;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};
