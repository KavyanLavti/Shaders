#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float vertices[] =
{
    -0.5, -0.5, 0,
    -0.25,0.5,0,
    0, -0.5, 0
};
float vertices2[] =
{
    0, -0.5, 0,
    0.25, 0.5, 0,
    0.5,-0.5,0
};
unsigned int indices[] =
{
    //We have to start from 0
    //this should be unsigned int not int only othwewise it doesn't work
    0,1,2,
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
const char* fragShaderSource2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.0,0.5,1.0,1.0);\n"
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

    unsigned int fragShader2;
    fragShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader2, 1, &fragShaderSource2, NULL);
    glCompileShader(fragShader2);
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

    unsigned int program2;
    program2 = glCreateProgram();
    glAttachShader(program2, vrtxShader);
    glAttachShader(program2, fragShader2);
    glLinkProgram(program2);

    glDeleteShader(vrtxShader);
    glDeleteShader(fragShader);
    glDeleteShader(fragShader2);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int VAO,VAO2,VBO2;
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO2);
    glGenVertexArrays(1, &VAO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    //vertex array must be bound befor boundig VBO and EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), &vertices2, GL_STATIC_DRAW);

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
        glUseProgram(program2);
        glBindVertexArray(0);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
