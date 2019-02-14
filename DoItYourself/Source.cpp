#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderCreator.h"
#include "TextureCreator.h"

//GLenum err;
//while ((err = glGetError()) != GL_NO_ERROR) {
//	std::cout << err;
//}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    float vertices[] =
    {
        0.5f,  0.5f, 0.0f, 0.7f,  0.7f,  0.7f,  1.0f, 1.0f,
       -0.5f,  0.5f, 0.0f, 0.3f,  0.5f,  0.9f,  0.0f, 1.0f,
       -0.5f, -0.5f, 0.0f, 0.1f,  0.8f,  0.2f,  0.0f, 0.0f,
	    0.5f, -0.5f, 0.0f, 0.25f, 0.33f, 0.17f, 1.0f, 0.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(true);
	TextureCreator textureCreator;
	unsigned int texture  = textureCreator.loadTexture("textures/star.png");
	unsigned int texture1 = textureCreator.loadTexture("textures/awesomeface.png");

    ShaderCreator shaderCreator;

    unsigned int vertexShader;
    vertexShader = shaderCreator.CreateShader(GL_VERTEX_SHADER, "shaders/vertexShader.txt");

    unsigned int fragmentShader;
    fragmentShader = shaderCreator.CreateShader(GL_FRAGMENT_SHADER, "shaders/fragmentShader.txt");
    shaderCreator.LinkProgram();

	shaderCreator.UseProgram();
	glUniform1i(glGetUniformLocation(shaderCreator.getProgram(), "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderCreator.getProgram(), "texture2"), 1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderCreator.UseProgram();

		//textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

        glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}