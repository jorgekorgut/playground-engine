#pragma once
#include "Mesh.h"
#include "shader/Shader.h"

class MeshLine : public Mesh {
    public:
    MeshLine(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
    : Mesh(vertices, indices) {
    }
    virtual void Render(Shader& shader) override {
        glBindVertexArray(VAO);
        glDrawElements(
        GL_LINES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
};
