#include "ReadShaderFromFile.h"

ReadShaderFromFile::ReadShaderFromFile()
{
    this->m_filepath = "";
}

std::string ReadShaderFromFile::ReadContentsFromFile()
{
    if (this->m_filepath != "")
    {
        std::stringstream build;
        std::string line;
        std::ifstream fi;
        fi.open(this->m_filepath);

        while (std::getline(fi, line))
        {
            build << line << "\n";
        }
        fi.close();
        return build.str();
    }
    else
        return "";
}

void ReadShaderFromFile::setFilePath(const char* filePath)
{
    this->m_filepath = filePath;
}