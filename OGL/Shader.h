#pragma once

#include <GL/glew.h>
class Shader
{
private:
    GLuint mProgram;
public:
    Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
    virtual ~Shader();
    GLuint GetProgram();
    void Use();
};

