#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
const char* fragmentShaderSourceOrange = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor,1.0f);\n"
"}\n\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void  processInput(GLFWwindow* window)
{
	//glfwGetKey ���ذ����Ƿ����ڱ�����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//�ж�esc�����û�а��£�������GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);

}

int main()
{

	//��ʼ��GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//����ģʽ

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//��������
	if (window == NULL)
	{
		cout << "Failed to Create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//�����ڵ�����������Ϊ��ǰ�̵߳���������
	//ע��ú���������GLFW�ڵ������ڴ�С��ʱ����øú���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);//���ô���ά�� ǰ�����������ƴ������½�λ�� ���Ĳ���������Ⱦ���ڵĿ����

	//����������ɫ������
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//����ɫ����Դ�븽�ӵ���ɫ�������ϲ�����(��ɫ�����󣬴���Դ���ַ�������������ɫ��������Դ�룬NULL)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//������ɫ������
	glCompileShader(vertexShader);

	int sucess;
	char inflog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, inflog);
		cout << "ERROR::SHADER::VETTEX::COMPILATION_FAILED\n" << inflog << endl;
	}

	//����ͬ��
	unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
	glCompileShader(fragmentShaderOrange);

	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, inflog);
		cout << "ERROR::SHADER::PRAGMENT::COMPILATION_FAILED\n" << inflog << endl;
	}
	

	//�������õ���ɫ�����ӵ���ɫ������
	unsigned int shaderProgramOrange = glCreateProgram();//����һ�����򣬲����ش�����������ID����
	//����ɫ�����ӵ�����
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	//����,�õ�һ���������
	glLinkProgram(shaderProgramOrange);
	glGetProgramiv(shaderProgramOrange, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, inflog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << inflog << endl;
	}
	


	//����֮��ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(shaderProgramOrange);


	float vertices[] = {
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};
	float secondvertices[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//ʹ�ú�����һ������ID����һ��VBO��VEO����
	unsigned int VBO[2],VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	//�״ΰ�VAO
    glBindVertexArray(VAO[0]);
	//VBO�Ļ���������GL_ARRAY_BUFFER��ʹ�ð󶨺������½��Ļ������󶨵�GL_ARRAY_BUFFERĿ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//��֮ǰ����Ķ������ݸ��Ƶ���ǰ�󶨻����ڴ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//����Ϊ��������ֵ
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//����Ϊ��������ֵ
	glEnableVertexAttribArray(1);



	//�����Ⱦѭ��(���е���Ⱦ�����ڸ�ѭ����ִ��)
	while (!glfwWindowShouldClose(window))//����Ƿ���Ҫ�˳�
	{

		glClearColor(0.2f,0.3f,0.3f,1.0f);//״̬���ú���
		glClear(GL_COLOR_BUFFER_BIT);//״̬ʹ�ú���
		processInput(window);

		//����uniform��ʱ��ǵü�����ɫ��
		glUseProgram(shaderProgramOrange);

		//float timevalue = glfwGetTime();
		//float greenvalue = (sin(timevalue) / 2.0f) + 0.5f;
		//int vertexColorValue = glGetUniformLocation(shaderProgramOrange, "ourColor");//�ҵ�uniform����
		//glUniform4f(vertexColorValue, 0.0f ,greenvalue, 0.0f, 1.0f);//���ĸ������ֱ�ΪRGBA
		

		glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES,0, 3);

		glfwPollEvents();//�����û��ʲô�����¼�����������Ӧ�Ļص�����
		glfwSwapBuffers(window);//������ɫ���壨������GLFW����ÿ��������ɫֵ�Ĵ󻺳壩 ʹ��˫���壨����ǰ�󻺳壩
		
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderProgramOrange);
	//����������Դ��ȷ�˳�Ӧ�ó���
	glfwTerminate();
	return 0;
}
