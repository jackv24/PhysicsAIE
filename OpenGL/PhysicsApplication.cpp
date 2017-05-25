#include "PhysicsApplication.h"

#include "RigidBody.h"
#include "Circle.h"
#include "Plane.h"
#include "Box.h"

using namespace glm;

bool PhysicsApplication::startup()
{
	glfwInit();

	window = glfwCreateWindow(1280, 720,
		"Computer Graphics",
		nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);


	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	Gizmos::create(65535U, 65535U, 65535U, 65535U);

	camera.radius = 1;

	CreateScene();

	return true;
}

void PhysicsApplication::shutdown()
{
	Gizmos::destroy();

	glfwDestroyWindow(window);


	glfwTerminate();
}

bool resetPressed = false;

bool PhysicsApplication::update()
{
	//Reset scene when button is initially pressed
	if (glfwGetKey(window, GLFW_KEY_R))
	{
		if (!resetPressed)
			CreateScene();

		resetPressed = true;
	}
	else
		resetPressed = false;

	camera.update(window);

	float dt = 1.0f / 60.0f;
	
	//Update physics bodies
	for (auto it = m_physicsObjects.begin(); it != m_physicsObjects.end(); ++it)
	{
		PhysicsObject* obj = *it;
		obj->Update(dt);

		//Check this object with everything further up the list
		for (auto it2 = it; it2 != m_physicsObjects.end(); ++it2)
		{
			if (it != it2)
			{
				PhysicsObject* obj2 = *it2;
				obj2->CheckCollisions(obj);
			}
		}
	}

	//TODO: sleep 1000*dt

	return (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}

void PhysicsApplication::draw()
{
	mat4 view = camera.getView();
	mat4 projection = camera.getProjection();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	Gizmos::clear();

	//Gizmos::addTransform(glm::mat4(1));
	//vec4 orange(1, 0.7f, 0.2f, 1.0f);
	//vec4 red(1, 0, 0, 1);
	//vec4 white(0.5f, 0.5f, 0.5f, 1.0f);
	//vec4 black(0, 0, 0, 1);

	////Draw grid
	//for (int i = 0; i < 21; ++i)
	//{
	//	Gizmos::add2DLine(vec2(-10 + i, 10), vec2(-10 + i, -10), i == 10 ? orange : white);
	//	Gizmos::add2DLine(vec2(10, -10 + i), vec2(-10, -10 + i), i == 10 ? orange : white);
	//}

	//Draw physics objects
	for (auto it = m_physicsObjects.begin(); it != m_physicsObjects.end(); ++it)
	{
		((PhysicsObject*)*it)->Draw();
	}

	//Draw gizmos
	Gizmos::draw2D(projection * view);
	
	glfwSwapBuffers(window);
	glfwPollEvents();

	day++;
}

void PhysicsApplication::CreateScene()
{
	//Reset scene
	m_physicsObjects.clear();

	//Add new physics objects to list
	m_physicsObjects.push_back(new Plane(glm::vec2(0, -5), glm::vec2(0.5f, 1)));
	m_physicsObjects.push_back(new Plane(glm::vec2(0, -5), glm::vec2(-0.5f, 1)));
	m_physicsObjects.push_back(new Box(glm::vec2(-3, 5), 2.0f, 1.0f, glm::vec2(0), 2.0f, 0.25f));
	m_physicsObjects.push_back(new Circle(glm::vec2(0), 1.0f, glm::vec2(1, 10), 1.0f, 0));
	m_physicsObjects.push_back(new Circle(glm::vec2(2), 1.0f, glm::vec2(1, 10), 1.0f, 0));
	m_physicsObjects.push_back(new Circle(glm::vec2(-1), 0.5f, glm::vec2(-1, 0), 0.5f, 0));
	//m_physicsObjects.push_back(new Circle(glm::vec2(3), 0.5f, glm::vec2(1, 0), 0.5f, 0));
	//m_physicsObjects.push_back(new Circle(glm::vec2(0, 3), 0.5f, glm::vec2(1, 6), 0.5f, 0));
}
