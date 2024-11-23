#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class camera
{
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraDir;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 WorldUp = glm::vec3(0, 1, 0);
	glm::vec3 dir;
	float pitch = 0.0;
	float yaw = -90;

	camera(glm::vec3 pos, glm::vec3 dir)
	{
		cameraPos = pos;
		cameraDir = (dir);
		cameraRight = (glm::cross(WorldUp, cameraDir));
	}
	void CameraMovementInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			cameraPos += glm::normalize(dir) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			cameraPos -= glm::normalize(dir) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			cameraPos += glm::normalize(cameraRight) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			cameraPos -= glm::normalize(cameraRight) * cameraSpeed;
		}
	}
	void updateVec()
	{
		cameraRight = (glm::cross(WorldUp, cameraDir));
		cameraUp = (glm::cross(cameraRight, cameraDir));
	}
	void look(double xpos, double ypos)
	{
		xpos *= lookSpeed;
		ypos *= lookSpeed;

		yaw += xpos;
		pitch -= ypos;

		if (pitch > 89)pitch = 89;
		if (pitch < -89)pitch = -89;

		cameraDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraDir.y = sin(glm::radians(pitch));
		cameraDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		dir = cameraDir;
		dir.y = 0;
	}
	glm::mat4 getLookAtMatrix()
	{
		return glm::lookAt(cameraPos, cameraPos + cameraDir, WorldUp);
	}
private:
	float cameraSpeed=0.01f;
	float lookSpeed=0.05f;
};
#endif
