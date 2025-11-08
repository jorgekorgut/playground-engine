#pragma once
#include "Mesh.h"
#include "shader/Shader.h"

class MeshLine : public Mesh {
    public:
    MeshLine(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
    : Mesh(vertices, indices) {
    }
    virtual void Render(Shader& shader) override;
};
