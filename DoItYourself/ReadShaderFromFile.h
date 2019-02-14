#ifndef READ_SHADER_FROM_FILE
#define READ_SHADER_FROM_FILE
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>

class ReadShaderFromFile
{
private:
    const char* m_filepath;

public:
    ReadShaderFromFile();
    std::string ReadContentsFromFile();
    void setFilePath(const char* filePath);
};
#endif