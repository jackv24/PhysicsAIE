#include <glm/glm/ext.hpp>
#include "Camera.h"

void Camera::update(GLFWwindow* window)
{
	float multiplier = 1.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) multiplier = 10.0f;

	if (glfwGetKey(window, GLFW_KEY_Q)) radius = radius - 0.05f * multiplier;
	if (glfwGetKey(window, GLFW_KEY_E)) radius = radius + 0.05f * multiplier;

	if (glfwGetKey(window, GLFW_KEY_W)) pos.y += 0.5f * multiplier;
	if (glfwGetKey(window, GLFW_KEY_S)) pos.y -= 0.5f * multiplier;
	if (glfwGetKey(window, GLFW_KEY_A)) pos.x -= 0.5f * multiplier;
	if (glfwGetKey(window, GLFW_KEY_D)) pos.x += 0.5f * multiplier;
}

mat4 Camera::getView()
{
	return glm::lookAt(vec3(pos.x, pos.y, 10*radius), vec3(pos.x, pos.y, 0), vec3(0, 1, 0));
}

mat4 Camera::getProjection()
{
	glm::mat4 orthomatrix;
	float left = -1.28f;
	float right = 1.28f;
	float top = 0.72f;
	float bottom = -0.72f;
	static float Znear = 0.01f;
	static float Zfar = 1000; 


	orthomatrix[0].x = 2.0f / (right - left);
	orthomatrix[0].y = 0;
	orthomatrix[0].z = 0;
	orthomatrix[0].w = -(right + left) / (right - left);

	orthomatrix[1].x = 0;
	orthomatrix[1].y = 2.0f / (top - bottom);
	orthomatrix[1].z = 0;
	orthomatrix[1].w = -(top + bottom) / (top - bottom);

	orthomatrix[2].x = 0;
	orthomatrix[2].y = 0;
	orthomatrix[2].z = -2.0f / (Zfar - Znear);
	orthomatrix[2].w = (Znear + Zfar) / (Znear - Zfar);

	orthomatrix[3].x = 0;
	orthomatrix[3].y = 0;
	orthomatrix[3].z = -(Zfar + Znear) / (Zfar - Znear);
	orthomatrix[3].w = 1;

	//mat4 perspective = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	return orthomatrix;
}