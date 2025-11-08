#include "ModelPlane.h"
#include "Mesh.h"
#include <iostream>
#include <shader/Shader.h>

ModelPlane::ModelPlane(int numCol, int numRow)
: numCol(numCol), numRow(numRow) {
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh::Vertex vertex;

    int numVertexX = numCol + 1;
    int numVertexY = numRow + 1;

    float distanceX = 1.0f / std::max((numVertexX - 1), 1);
    float distanceY = 1.0f / std::max((numVertexY - 1), 1);

    for(int i = 0; i < numVertexY; i++) {
        for(int j = 0; j < numVertexX; j++) {
            vertex.Position =
            glm::vec3((float)j * distanceX - 0.5f, (float)i * distanceY - 0.5f, 0);
            vertex.Normal = glm::vec3(0, 0, 1);
            vertices.push_back(vertex);
        }
    }

    int maxVertexIndex = numVertexY * numVertexX - 1;

    for(int i = 0; i < numVertexY - 1; i++) {
        for(int j = 0; j < numVertexX - 1; j++) {
            indices.push_back(i * numVertexX + j);
            indices.push_back((i + 1) * numVertexX + j);
            indices.push_back(i * numVertexX + j + 1);

            indices.push_back(i * numVertexX + j + 1);
            indices.push_back((i + 1) * numVertexX + j);
            indices.push_back((i + 1) * numVertexX + j + 1);
        }
    }

    meshes.emplace_back(std::make_shared<Mesh>(vertices, indices));
}
