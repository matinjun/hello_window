#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_s.h>

#include <iostream>

/*---------�Զ��庯����������----------------*/
// Ϊ��Ƶ���ĸı�۲촰�ڴ�С����Ҫע��һ���ص����������ϵ��õĺ�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// ��װ���뺯������ĳ������Ϊ����
void processInput(GLFWwindow* window);

/*-----------------�Զ����������------------------*/
// ��������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

int main() {
	/*----------------------�汾��鼰��ʼ������-----------------------*/
	// ��һ�д�����������
	glfwInit();
	// �����д���ȷ��opengl�İ汾��3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ʹ��core-profile����ʹ��opengl����С�Ӽ�
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*-----------------------�������ڣ���鹤���Ƿ���ȫ����-----------------------*/

	// �������ڣ����ߣ�����
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// ����ǰ���ڱ�Ϊ������
	glfwMakeContextCurrent(window);
	// ����glfw��ÿ�ε������ڴ�Сʱ���ú���frambuffer_size_callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ȷ��opengl����ָ���Ѿ���ȷ����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader my_shader("3.3.shader.vs", "3.3.shader.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ��һ��VAO����
	glBindVertexArray(VAO);

	// ��һ��VBO���󲢴�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// �������ݵĸ�ʽ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// �����ӦVBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// �����ӦVAO
	glBindVertexArray(0);



	/*--------------��Ⱦѭ��------------------*/
	// Ϊ��ʹ��ʾ��һ��������ֱ������˳����˳�
	// ���е���Ⱦ����ҲӦ�������ѭ�����
	while (!glfwWindowShouldClose(window)) {
		// ĳЩ��Ҫ�����빤��
		processInput(window);

		// ��Ⱦָ��
		// -----------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڵ���ɫ��ע�⣬������ı䴰�ڵ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); // �����ô�����ɫ��ı䴰�ڵ���ɫ��ע�⣬����������ɫ��ֻ�Ǹı�


		// ����������
		// ----------
		my_shader.use();// ������ˮ��

		// update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(my_shader.ID, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// now render the triangle
		glBindVertexArray(VAO); // ѡ��Ҫ���Ƶ�VAO
		glDrawArrays(GL_TRIANGLES, 0, 3); // ����


		// ����¼��ͽ���˫����
		glfwSwapBuffers(window); // ����˫���棬�����һ��
		glfwPollEvents(); // ����glfw��Ҫ��Ӧ�¼�����������룬�������룩
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(my_shader.ID);

	// �ͷ�ʹ�õ���Դ�����ͷ��ڴ�ȵ�
	glfwTerminate();
	return 0;
}


// Ϊ��Ƶ���ĸı�۲촰�ڴ�С����Ҫע��һ���ص����������ϵ��õĺ�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// ���Ϊ���ù۲�ĵĴ��ڣ������Ѿ����õ��ܴ��ڣ���С
	// ���Ϊ���½�����(x,y)���ұ�Ϊ��ȣ��߶�
	glViewport(0, 0, width, height);
}

// ��װ���뺯������ĳ������Ϊ�������˴����Է�װ�������
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // ��ü��̵����룬�鿴�Ƿ����˳�����
	{ 
		glfwSetWindowShouldClose(window, true); // ����õ���<esc>������Ҫֻ��Ҫ������Ӧ��״̬����
	}
}
