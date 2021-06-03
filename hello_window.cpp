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
	//glfwGetKey 返回按键是否正在被按下
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//判断esc，如果没有按下，将返回GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);

}

int main()
{

	//初始化GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//核心模式

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//创建窗口
	if (window == NULL)
	{
		cout << "Failed to Create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//将窗口的上下文设置为当前线程的主上下文
	//注册该函数，告诉GLFW在调整窗口大小的时候调用该函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);//设置窗口维度 前两个参数控制窗口左下角位置 三四参数控制渲染窗口的宽与高

	//创建顶点着色器对象
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//把着色器的源码附加到着色器对象上并编译(着色器对象，传递源码字符串的数量，着色器真正的源码，NULL)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//编译着色器对象
	glCompileShader(vertexShader);

	int sucess;
	char inflog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, inflog);
		cout << "ERROR::SHADER::VETTEX::COMPILATION_FAILED\n" << inflog << endl;
	}

	//过程同上
	unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
	glCompileShader(fragmentShaderOrange);

	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, inflog);
		cout << "ERROR::SHADER::PRAGMENT::COMPILATION_FAILED\n" << inflog << endl;
	}
	

	//将创建好的着色器链接到着色器程序
	unsigned int shaderProgramOrange = glCreateProgram();//创建一个程序，并返回创建程序对象的ID引用
	//将着色器附加到程序
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	//链接,得到一个程序对象
	glLinkProgram(shaderProgramOrange);
	glGetProgramiv(shaderProgramOrange, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, inflog);
		cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << inflog << endl;
	}
	


	//链接之后删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(shaderProgramOrange);


	float vertices[] = {
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
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

	//使用函数和一个缓冲ID生成一个VBO和VEO对象
	unsigned int VBO[2],VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	//首次绑定VAO
    glBindVertexArray(VAO[0]);
	//VBO的缓冲类型是GL_ARRAY_BUFFER，使用绑定函数把新建的缓冲对象绑定到GL_ARRAY_BUFFER目标上
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//把之前定义的顶点数据复制到当前绑定缓冲内存中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//参数为顶点属性值
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//参数为顶点属性值
	glEnableVertexAttribArray(1);



	//添加渲染循环(所有的渲染操作在该循环中执行)
	while (!glfwWindowShouldClose(window))//检查是否需要退出
	{

		glClearColor(0.2f,0.3f,0.3f,1.0f);//状态设置函数
		glClear(GL_COLOR_BUFFER_BIT);//状态使用函数
		processInput(window);

		//更改uniform的时候记得激活着色器
		glUseProgram(shaderProgramOrange);

		//float timevalue = glfwGetTime();
		//float greenvalue = (sin(timevalue) / 2.0f) + 0.5f;
		//int vertexColorValue = glGetUniformLocation(shaderProgramOrange, "ourColor");//找到uniform索引
		//glUniform4f(vertexColorValue, 0.0f ,greenvalue, 0.0f, 1.0f);//后四个变量分别为RGBA
		

		glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES,0, 3);

		glfwPollEvents();//检查有没有什么触发事件，并调用相应的回调函数
		glfwSwapBuffers(window);//交换颜色缓冲（储存着GLFW窗口每个像素颜色值的大缓冲） 使用双缓冲（交换前后缓冲）
		
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderProgramOrange);
	//清理所有资源正确退出应用程序
	glfwTerminate();
	return 0;
}
