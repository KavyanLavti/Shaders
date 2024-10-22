#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
void renderloop(GLFWwindow* window)
{
    inputHandler(window);
    glClearColor(1.0, 0, 0, 0.);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}
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
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetWindowShouldClose(window, GLFW_FALSE);
    while (!glfwWindowShouldClose(window))
    {
        renderloop(window);
    }
    std::cout << "done" << std::endl;
    glfwTerminate();
    return 0;
}
