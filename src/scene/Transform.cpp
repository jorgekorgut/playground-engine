#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

Transform::Transform(std::shared_ptr<Transform> parent,
glm::vec3& position,
glm::vec3& rotation,
glm::vec3& scale)
: parent(parent), position(position), rotation(rotation), scale(scale) {
}

glm::mat4 Transform::GetModelMatrix() const {
    glm::mat4 model(1.0f);
    model = glm::translate(model, position); // translate it down so it's at the center of the scene
    model = model * glm::mat4_cast(glm::quat(glm::radians(-rotation)));
    model = glm::scale(model, scale);

    if(parent != nullptr) {
        model = parent->GetModelMatrix() * model;
    }

    return model;
}
