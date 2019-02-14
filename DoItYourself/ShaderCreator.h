#ifndef SHADER_CREATOR_H
#define SHADER_CREATOR_H

#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include "ReadShaderFromFile.h"

class ShaderCreator
{
private:
    ReadShaderFromFile* readShader;
    const char* shaderData;
    unsigned int shader;
    std::string textRead;
    unsigned int shaderProgram;
	void checkForErrors(GLenum);
public:
    ShaderCreator();
    unsigned int CreateShader(GLenum shaderType, const char* shaderPath);
    const char* getShaderData();
    void UseProgram();
    void LinkProgram();
	unsigned int getProgram();
};

#endif