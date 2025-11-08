#pragma once
#include "Model.h"
#include "shader/Shader.h"
#include "Mesh.h"
#include <vector>

class ModelSky : public Model {
    public:
    ModelSky() {
        std::vector<Mesh::Vertex> vertices;
        std::vector<unsigned int> indices;

        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0, 0, 0) }));
        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0, 0, 0) }));
        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0, 0, 0) }));
        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0, 0, 0) }));
        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 0) }));
        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0) }));
        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0, 0, 0) }));
        vertices.emplace_back(
        Mesh::Vertex({ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0, 0, 0) }));

        indices.emplace_back(0);
        indices.emplace_back(1);
        indices.emplace_back(2);
        indices.emplace_back(2);
        indices.emplace_back(3);
        indices.emplace_back(0);
        indices.emplace_back(4);
        indices.emplace_back(1);
        indices.emplace_back(0);
        indices.emplace_back(0);
        indices.emplace_back(5);
        indices.emplace_back(4);
        indices.emplace_back(2);
        indices.emplace_back(6);
        indices.emplace_back(7);
        indices.emplace_back(7);
        indices.emplace_back(3);
        indices.emplace_back(2);
        indices.emplace_back(4);
        indices.emplace_back(5);
        indices.emplace_back(7);
        indices.emplace_back(7);
        indices.emplace_back(6);
        indices.emplace_back(4);
        indices.emplace_back(0);
        indices.emplace_back(3);
        indices.emplace_back(7);
        indices.emplace_back(7);
        indices.emplace_back(5);
        indices.emplace_back(0);
        indices.emplace_back(1);
        indices.emplace_back(4);
        indices.emplace_back(2);
        indices.emplace_back(2);
        indices.emplace_back(4);
        indices.emplace_back(6);

        meshes.emplace_back(std::make_shared<Mesh>(vertices, indices));
    }

    virtual ~ModelSky() {
    }
};
