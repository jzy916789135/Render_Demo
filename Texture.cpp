/*
* 
* 
#include <glad/glad.h>
#include<glfw/glfw3.h>
#include<shader.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<iostream>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Texture", NULL, NULL);
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

	Shader ourShder("shadervs.txt", "shaderfs.txt");



	float vertices[] = {
		//     ---- 位置 ----           - 纹理坐标 -
			0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,      1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,      0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,      0.0f, 1.0f
	};
	unsigned int indices[] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);




	//生成纹理对象
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);//输入生成纹理的数量，然后把它们储存在第二个参数的unsigned int数组(这里只有一个值)
	glBindTexture(GL_TEXTURE_2D, texture1);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 加载图片
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);//宽度 高度 颜色通道
	//生成纹理
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture1" << endl;
	}
	//释放图像内存
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);//宽度 高度 颜色通道
	//生成纹理
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture2" << endl;
	}
	//释放图像内存
	stbi_image_free(data);
	ourShder.use();
	glUniform1i(glGetUniformLocation(ourShder.ID, "texture1"), 0);
	ourShder.setInt("texture2", 1);
	ourShder.setFloat("Mixvalue", 0.0f);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//激活纹理单元，绑定
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		//设置位移，旋转
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, 0.5f*(float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShder.use();
		unsigned int transformLocation = glGetUniformLocation(ourShder.ID, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
		float Scale_change = (sin(glfwGetTime()*0.5f) / 2) + 0.5f;
		transform = glm::scale(transform, glm::vec3(Scale_change, Scale_change, Scale_change));
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &transform[0][0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;

}


*/