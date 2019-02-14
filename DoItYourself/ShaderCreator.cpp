#include "ShaderCreator.h"
#include <iostream>

ShaderCreator::ShaderCreator()
{
    this->readShader = new ReadShaderFromFile();
    this->shader = 0;
    this->shaderData = "";
    this->shaderProgram = glCreateProgram();
}

unsigned int ShaderCreator::CreateShader(GLenum shaderType, const char* shaderPath)
{
    this->shader = glCreateShader(shaderType);
    this->readShader->setFilePath(shaderPath);
    this->textRead = readShader->ReadContentsFromFile();
    this->shaderData = this->textRead.c_str();
    glShaderSource(this->shader, 1, &this->shaderData, NULL);
    glCompileShader(this->shader);
    glAttachShader(this->shaderProgram, this->shader);
	checkForErrors(GL_COMPILE_STATUS);
    return this->shader;
}

const char* ShaderCreator::getShaderData()
{
    return this->shaderData;
}

void ShaderCreator::LinkProgram()
{
    glLinkProgram(this->shaderProgram);
	checkForErrors(GL_LINK_STATUS);
}

void ShaderCreator::UseProgram()
{
    glUseProgram(this->shaderProgram);
}

void ShaderCreator::checkForErrors(GLenum value)
{
	int success;
	char infoLog[512];
	if (value == GL_COMPILE_STATUS)
	{
		glGetShaderiv(this->shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(this->shader, 512, NULL, infoLog);
			std::cout << "ERROR SHADER COMPILATION_FAILED\n" << infoLog << std::endl;
		};
	}
	else if (value == GL_LINK_STATUS)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR PROGRAM_LINKING_ERROR" << "\n" << infoLog << std::endl;
		}
	}
}

unsigned int ShaderCreator::getProgram()
{
	return this->shaderProgram;
}