#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;



Shader::Shader(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath)
{
    string vsSrc;
    string fsSrc;
    ifstream vsFile;
    ifstream fsFile;

    try
    {
        vsFile.open(vertexShaderPath);
        fsFile.open(fragmentShaderPath);
        stringstream vsStream, fsStream;
        vsStream << vsFile.rdbuf();
        fsStream << fsFile.rdbuf();

        vsFile.close();
        fsFile.close();

        vsSrc = vsStream.str();
        fsSrc = fsStream.str();
    }
    catch( exception e )
    {
        cout << "ERROR: File not read successfully" << endl;
    }

    const GLchar* vertexShaderSource    = vsSrc.c_str();
    const GLchar* fragmentShaderSource  = fsSrc.c_str();

    // Build and link shaders
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Fragment Shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Link shaders and create program
    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);

    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
        cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

GLuint Shader::GetProgram()
{
    return mProgram;
}

void Shader::Use()
{
    glUseProgram(mProgram);
}
