#pragma once
#include "Mesh.h"
#include "shader/Shader.h"
#include <vector>

class Model {
    public:
    Model() {
    }

    ~Model() {
    }

    virtual void Render(Shader& shader) {
        for(unsigned int i = 0; i < meshes.size(); i++) {
            meshes[i]->Render(shader);
        }
    }

    std::vector<std::shared_ptr<Mesh>> meshes;
};
