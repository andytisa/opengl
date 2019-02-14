#ifndef TEXTURE_CREATOR_H
#define TEXTURE_CREATOR_H
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

class TextureCreator
{
private:
	void loadImage(unsigned char*, int, int);
public:
	unsigned int loadTexture(const char*);

};


#endif

