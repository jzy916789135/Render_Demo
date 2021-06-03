/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void  processInput(GLFWwindow* window)
{
	//glfwGetKey 返回按键是否正在被按下
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//判断esc，如果没有按下，将返回GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);

}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800,600,"Shder",NULL,NULL);
	if (window == NULL)
	{
		cout << "Failed to Create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShder("shadervs.txt","shaderfs.txt");

	float vertices[] = {
		1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		0.0f,1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);

		ourShder.use();
		float Offset = 0.5f;
		//ourShder.setFloat("xoffset",Offset);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0,3);

		glfwPollEvents();//检查有没有什么触发事件，并调用相应的回调函数
		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}*/