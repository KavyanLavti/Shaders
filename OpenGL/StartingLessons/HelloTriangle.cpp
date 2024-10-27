#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float vertices[] =
{
    -0.5, -0.5, 0,
    0.5, -0.5, 0,
    0, 0.5, 0,
    1.0,0.5,0
};
int indices[] =
{
    1,2,3,
    2,3,4
};

const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0)in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0,0.5,0.0,1.0);\n"
"}\n\0";


void frame_resize_callback(GLFWwindow* window, int width, int height)
{
    glad_glViewport(0, 0, width, height);
}


void init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void inputHandler(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


/*void renderloop(GLFWwindow* window)
{
    inputHandler(window);
    glClearColor(1.0, 0, 0, 0.);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}*/
int main() 
{
    init();
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "lesson_1", NULL, NULL);
    if (window == NULL) 
    { 
        std::cout << "failed to create window";
        glfwTerminate();
        return -1; 
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_resize_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    unsigned int vrtxShader;
    vrtxShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vrtxShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vrtxShader);

    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);
    /*int  success;
    char infoLog[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }*/

    unsigned int program;
    program = glCreateProgram();
    glAttachShader(program, vrtxShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glDeleteShader(vrtxShader);
    glDeleteShader(fragShader);


    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        //renderloop(window);
        inputHandler(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
