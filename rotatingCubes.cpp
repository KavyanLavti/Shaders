#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h";

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/*float vertices[] =
{
    -0.5, -0.5, 0.5, 1.0 , 0 , 0, 0,0,
    0.5, -0.5, 0.5, 0 ,1 ,0,1,0,
    0, 0.5, 0.5, 0, 0 ,1,0,1,
    1.0,0.5,0.5, 1, 1, 0,1,1
    - 0.5, -0.5, -0.5, 1.0 , 0 , 0, 0,0,
    0.5, -0.5, -0.5, 0 ,1 ,0,1,0,
    0, 0.5, -0.5, 0, 0 ,1,0,1,
    1.0,0.5,-0.5, 1, 1, 0,1,1
};*/
float vertices[] = {
    // Positions          // Colors       // Texture Coords
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // 0
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 1
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // 2
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // 3
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,   1.0f, 1.0f, // 4
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   0.0f, 1.0f, // 5
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // 6
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f  // 7
};
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  -8.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int indices[] = {
    // Front face
    0, 1, 2,
    2, 3, 0,
    // Back face
    4, 5, 6,
    6, 7, 4,
    // Left face
    4, 0, 3,
    3, 7, 4,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Top face
    3, 2, 6,
    6, 7, 3,
    // Bottom face
    4, 5, 1,
    1, 0, 4
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)0);
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

    glm::mat4 IdendityM = glm::mat4(1.0);
    glm::mat4 Projection = glm::perspective(glm::radians(120.0f), 800.0f/600.0f, 0.01f, 100.0f);
    shader.setMat4("Projection", Projection);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        //glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::rotate(trans, glm::radians((float)glfwGetTime() * 100), glm::vec3(1.0f, 1.0f, 1.0f));
        /*trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 1));*/
        //renderloop(window);
        inputHandler(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 Model = glm::rotate(IdendityM, glm::radians(20.0f*i+20.0f*((i/3)-((i-1)/3))*(float)glfwGetTime()), glm::vec3(1.0f, 0.3f, 1.2f));
            glm::mat4 View = glm::translate(IdendityM, cubePositions[i]);
            shader.setMat4("Model", Model);
            shader.setMat4("View", View);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
       // int locationUniformMatrix = glad_glGetUniformLocation(shader.ID, "matrix");
        //glUniformMatrix4fv(locationUniformMatrix, 1, GL_FALSE, glm::value_ptr(trans));
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    glfwTerminate();
    return 0;
}
