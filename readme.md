# 窗口
## 配置
**Note**: 所有的环境都在**64位**下运行，**注意**
1. 确保有CMake，vs2019Comunity
2. [glfw3](https://www.glfw.org/download.html)，下载sourcepackage编译。<br>
[glad](https://glad.dav1d.de/)网站会按照要求自动生成配置文件。<br>
编译过程与生成细节具体细节见[learnopengl](https://learnopengl.com/Getting-started/Creating-a-window)。<br>
这步你会手动编译开源软件，一定要参考教材。
3. 最后需要配置vc++目录，同样[learnopengl](https://learnopengl.com/Getting-started/Creating-a-window)
## 代码部分
分为三个部分
- Init()部分，初始化必要的资源
- 创建窗口等对象，回调函数
- 渲染循环，实际上还要加上一个结束部分（释放资源glfwTerminate()）
