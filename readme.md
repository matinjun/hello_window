# ����
## ����
**Note**: ���еĻ�������**64λ**�����У�**ע��**
1. ȷ����CMake��vs2019Comunity
2. [glfw3](https://www.glfw.org/download.html)������sourcepackage���롣<br>
[glad](https://glad.dav1d.de/)��վ�ᰴ��Ҫ���Զ����������ļ���<br>
�������������ϸ�ھ���ϸ�ڼ�[learnopengl](https://learnopengl.com/Getting-started/Creating-a-window)��<br>
�ⲽ����ֶ����뿪Դ�����һ��Ҫ�ο��̲ġ�
3. �����Ҫ����vc++Ŀ¼��ͬ��[learnopengl](https://learnopengl.com/Getting-started/Creating-a-window)
## ���벿��
��Ϊ��������
- Init()���֣���ʼ����Ҫ����Դ
- �������ڵȶ��󣬻ص�����
- ��Ⱦѭ����ʵ���ϻ�Ҫ����һ���������֣��ͷ���ԴglfwTerminate()��
## ����֪ʶ
### vao, vbo, shader
1. openglʹ����ˮ�ߣ�����ά�ռ�ĵ��Ϊ��ά���ڵĵ㣬��֮����Ҫ������ˮ���֣�ÿ�����־���һ����GPU�����еĳ��򣬽���shader��������Ҫ��ɵ���vertex shader��fragrament shader������[�ο�](https://learnopengl.com/Getting-started/Hello-Triangle)
    1. ������ɫ���������Ϊ��ÿ��������д���
    2. ƬԪ��ɫ���������Ϊ��ÿ�����صĴ���
2. ���꣬VBO
    1. ����(x, y, z)����ֻ����[-1, 1]֮�䣬�����ᱻ�ü�����ʱ��ҪͶӰ�任
    2. VBOָGPU�еĻ������ͨ��������VBO�����ʡ�ʹ��glGenBuffers(num, &arrayVBO)������num��VBO������arrayVBO�ϡ�
     - VBO�����ͣ�ͨ��```glBindBuffer(GL_ARRAY_BUFFER, VBOIndex); ```��ĳ��VBO���������
     - ͨ��```glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);```���ڴ��е����ݸ��Ƶ�GPU������
        * ��һ������ָ����Ŀ�껺�������
        * �ڶ�������ָ�����ڴ�Ĵ�С
        * ������ָ���������ݵ���ʼ��ַ
        * ���ĸ�ָ�Կ�������ڴ洫�������ݵķ�ʽ���Ǹı仹�ǲ���ȵ�
            - ```GL_STREAM_DRAW```: the data is set only once and used by the GPU at most a few times.
            - ```GL_STATIC_DRAW```: the data is set only once and used many times.
            - ```GL_DYNAMIC_DRAW```: the data is changed a lot and used many times.
    3. shader����ɫ����
     - shader����ˮ�ߵ�һ���֣����ڴ�����������ݲ����
     - ����ֻ��Ҫʵ��vertex shader��fragment shader����
```c++
// ����shader���󣬲���������
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER); // �˴��Ĳ�����ָshader������

glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // ��shader��ĳ������Ƭ����ϵ����
glCompileShader(vertexShader); // ����

unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);

// ����������󣬲�������õ�shader������������
unsigned int shaderProgram;
shaderProgram = glCreateProgram();

glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

// ʹ���������
glUseProgram(shaderProgram);

// ֮��shader����ʹ�ã����ڲ�ʹ�õ�shader������Ҫɾ��
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```
3. VAO��ָ���洢vbo�󶨵����ԡ�**������VAOΪ��λ**
    - ����ָ��ν���GPU�еĻ��棬����ʲô��ʽ���ʻ���
    - ���ڻ��������```glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);```��������η��ʶ��㻺��
       * ��һ��ָ������Ҫ�����ĸ��������ԣ�����������λ��
       * �ڶ���������ÿ����������Ը�������x y z
       * ������ָÿ�����Ե�����
       * ���ĸ�Ĭ��ΪGL_FALSE
       * �����ָһ������Ĵ�С
       * ������ָ����ڻ�����ʼ��ƫ���ӽ���
    - ��������```glEnableVertexAttribArray(0)```����Ϊ��������λ��
    - ������ʵ�Ǹı���ĳ��״̬��VAO��������洢��Щ״̬��������Ӧ��VBO״̬�󶨣�VBO�����ԣ����ݵȣ�
       * Ҫʹ��VAO����Ҫ����Ҫ�洢�Ļ������ǰ���ɲ������ͣ�֮�����ʱ�����°󶨣��������£�
       * ����VAOʱ�����Ǹ��㿪ʼ���κκ����������Ե��ö����洢��VAO��
```c++
// ..:: Initialization code (done once (unless your object frequently changes)) :: ..

// 0. generate VAO
unsigned int VAO;
glGenVertexArrays(1, &VAO);

// 1. bind Vertex Array Object
glBindVertexArray(VAO);
// 2. copy our vertices array in a buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. then set our vertex attributes pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);  

  
[...]

// ..:: Drawing code (in render loop) :: ..
// 4. draw the object
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
someOpenGLFunctionThatDrawsOurTriangle();   
```

4. ����EBO
����opengl����������ƬΪ��Ԫ���ƣ�������һ�������ʱ����ֶ���㸴�õ������Ϊ��ʡ�ռ䣬ʹ��EBO���������GPU�д������������÷���VBO����
```c++
// ..:: Initialization code :: ..
// 1. bind Vertex Array Object
glBindVertexArray(VAO);
// 2. copy our vertices array in a vertex buffer for OpenGL to use
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. copy our index array in a element buffer for OpenGL to use
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
// 4. then set the vertex attributes pointers
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);  

[...]
  
// ..:: Drawing code (in render loop) :: ..
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)
glBindVertexArray(0);
```

5, ���ڽ�󣬲�ʹ��ʱ���������
```c++
	// �����ӦVBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// �����ӦVAO
	glBindVertexArray(0);
```

<HR>

### ���ڸ�������Լ�����
1. [��������λ���](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.2.hello_triangle_indexed/hello_triangle_indexed.cpp)
2. [ʹ�ö��VAO, VBO](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.4.hello_triangle_exercise2/hello_triangle_exercise2.cpp)
3. [ʹ�ö��shader���Ʋ�ͬ����ɫ](https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/2.5.hello_triangle_exercise3/hello_triangle_exercise3.cpp)

### С�ܽ�
������
1. init
2. ���ڳ�ʼ��
3. ����shader
4. ͨ��VBO�������ݵ�GPU����������ʹ��VAO���벻ͬ������
5. ѭ����Ⱦ
6. �ͷ�
