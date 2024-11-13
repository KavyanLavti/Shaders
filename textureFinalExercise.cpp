#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h";

float vertices[] =
{
    -0.5, -0.5, 0, 1.0 , 0 , 0, 0,0,
    0.5, -0.5, 0, 0 ,1 ,0,1,0,
    0, 0.5, 0, 0, 0 ,1,0,1,
    1.0,0.5,0, 1, 1, 0,1,1
};
int indices[] =
{
    0, 1, 2, // first triangle
    1, 2, 3  // second triangle
};
float amount = 0.1;
float updown = 0;
static bool upKeyPressed = false;
static bool downKeyPressed = false;


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
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !upKeyPressed) {
        updown += amount;
        if (updown > 1) updown = 1;
        upKeyPressed = true;  // Mark the key as pressed
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
        upKeyPressed = false;  // Reset when the key is released
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !downKeyPressed) {
        updown -= amount;
        if (updown < 0) updown = 0;
        downKeyPressed = true;  // Mark the key as pressed
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
        downKeyPressed = false;  // Reset when the key is released
    }
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader = Shader("Shader.vert", "Shader.frag");

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    unsigned int texture, texture1;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("D:/Downloads/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "LOL";
    }
    stbi_image_free(data);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("D:/Downloads/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Bhadwa";
    }
    stbi_image_free(data);
    shader.use();
    shader.setInt("tex", 0);
    shader.setInt("tex2", 1);

    while (!glfwWindowShouldClose(window))
    {
        //renderloop(window);
        inputHandler(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float t = glfwGetTime();
        float sinT = (sin(t) / 2.0) + 0.5;
        //int locationUniformColor = glGetUniformLocation(program, "outColor");
        //std::cout << updown;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        shader.use();
        shader.setFloat("FuckFace", updown);
        shader.setFloat("offset", sin(t) / 3.0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    glfwTerminate();
    return 0;
}
