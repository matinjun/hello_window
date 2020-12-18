#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

/*---------自定义函数声明部分----------------*/
// 为了频繁的改变观察窗口大小，需要注册一个回调函数（不断调用的函数）
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 封装输入函数，以某个窗口为参数
void processInput(GLFWwindow* window);

/*-----------------自定义变量部分------------------*/
// 窗口设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main() {
	/*----------------------版本检查及初始化部分-----------------------*/
	// 第一行代码必须是这个
	glfwInit();
	// 这两行代码确保opengl的版本是3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 使用core-profile，即使用opengl的最小子集
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*-----------------------创建窗口，检查工具是否齐全部分-----------------------*/

	// 创建窗口：宽，高，名称
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// 将当前窗口变为主窗口
	glfwMakeContextCurrent(window);
	// 告诉glfw在每次调整窗口大小时调用函数frambuffer_size_callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 确保opengl函数指针已经正确载入
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*--------------渲染循环------------------*/
	// 为了使显示不一闪而过，直到点击退出才退出
	// 所有的渲染工作也应该在这个循环完成
	while (!glfwWindowShouldClose(window)) {
		// 某些必要的输入工作
		processInput(window);

		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置窗口的颜色，注意，并不会改变窗口的颜色
		glClear(GL_COLOR_BUFFER_BIT); // 在设置窗口颜色后改变窗口的颜色，注意，并不设置颜色，只是改变


		// 检查事件和交换双缓存
		glfwSwapBuffers(window); // 采用双缓存，与课堂一样
		glfwPollEvents(); // 告诉glfw需要响应事件（如鼠标输入，键盘输入）
	}

	// 释放使用的资源，如释放内存等等
	glfwTerminate();
	return 0;
}


// 为了频繁的改变观察窗口大小，需要注册一个回调函数（不断调用的函数）
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// 理解为设置观察的的窗口（基于已经设置的总窗口）大小
	// 左边为左下角坐标(x,y)，右边为宽度，高度
	glViewport(0, 0, width, height);
}

// 封装输入函数，以某个窗口为参数，此处可以封装多个函数
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // 获得键盘的输入，查看是否是退出窗口
	{ 
		glfwSetWindowShouldClose(window, true); // 如果得到了<esc>键，需要只需要设置相应的状态即可
	}
}
