#pragma once

#include <conio.h>
#include <gl_core_4_4.h>
#include <glfw-3.1.2\include\GLFW\glfw3.h>
#include <aie/Gizmos.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <list>

#include "Application.h"
#include "Camera.h"
#include "PhysicsObject.h"

class PhysicsApplication : public Application
{
public:

	virtual bool startup();
	virtual void shutdown();
	virtual bool update();
	virtual void draw();

	void CreateScene();

	int day = 0;

	Camera camera;

	GLuint shaderID;

private:
	std::list<PhysicsObject*> m_physicsObjects;

	bool m_mouseDown = false;
};
