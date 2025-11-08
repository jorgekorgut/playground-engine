#include "Shader.h"

Shader::Shader(int ID) : ID(ID) {
}

void Shader::use() {
    if(ID == -1) {
        std::cerr << "Shader was not loaded correctly initialized" << std::endl;
        return;
    }
    glUseProgram(static_cast<unsigned int>(ID));
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(getUniformLocation(name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(getUniformLocation(name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(getUniformLocation(name.c_str()), value);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) {
    glUniform4f(getUniformLocation(name.c_str()), x, y, z, w);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
    glUniform3f(getUniformLocation(name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& name, glm::vec3 pos) {
    glUniform3f(getUniformLocation(name.c_str()), pos.x, pos.y, pos.z);
}

void Shader::setMat4(const std::string& name, glm::mat4& mat) {
    glUniformMatrix4fv(getUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat3(const std::string& name, glm::mat3& mat) {
    glUniformMatrix3fv(getUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

GLint Shader::getUniformLocation(const std::string& name) const {
    GLint location = -1;
    std::unordered_map<std::string, GLint>::const_iterator foundLocation =
    uniformLocationCache.find(name);

    if(foundLocation != uniformLocationCache.end()) {
        location = foundLocation->second;
    } else {
        location                   = glGetUniformLocation(ID, name.c_str());
        uniformLocationCache[name] = location;
    }
    return location;
}
