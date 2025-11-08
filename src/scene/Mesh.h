#pragma once

#include "shader/Shader.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Mesh {
    public:
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
    };
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    Mesh(Mesh& other);
    ~Mesh();
    void UpdateMesh();
    virtual void Render(Shader& shader);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    protected:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    void setupMesh();
};
