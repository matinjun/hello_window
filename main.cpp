#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	/*--------------��Ⱦѭ��------------------*/
	// Ϊ��ʹ��ʾ��һ��������ֱ������˳����˳�
	// ���е���Ⱦ����ҲӦ�������ѭ�����
	while (!glfwWindowShouldClose(window)) {
		// ĳЩ��Ҫ�����빤��
		processInput(window);

		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���ô��ڵ���ɫ��ע�⣬������ı䴰�ڵ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); // �����ô�����ɫ��ı䴰�ڵ���ɫ��ע�⣬����������ɫ��ֻ�Ǹı�


		// ����¼��ͽ���˫����
		glfwSwapBuffers(window); // ����˫���棬�����һ��
		glfwPollEvents(); // ����glfw��Ҫ��Ӧ�¼�����������룬�������룩
	}

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
