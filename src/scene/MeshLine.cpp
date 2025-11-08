#include "MeshLine.h"
#include <glad/glad.h>

void MeshLine::Render(Shader& shader) {
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
