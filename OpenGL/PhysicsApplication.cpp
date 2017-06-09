#include "PhysicsApplication.h"

#include "RigidBody.h"
#include "Circle.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"

using namespace glm;

Circle* lastCircle = nullptr;

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

	camera.radius = 2;

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

	bool mouseDown = glfwGetMouseButton(window, 0);

	double x0, y0;
	glfwGetCursorPos(window, &x0, &y0);

	mat4 view = camera.getView();
	mat4 projection = camera.getProjection();

	glm::vec3 windowCoords = glm::vec3(x0, y0, 0);
	glm::vec4 viewport = glm::vec4(0, 0, 1280, 720);
	glm::vec3 worldCoords = glm::unProject(windowCoords, view, projection, viewport);

	glm::vec2 m_mousePoint = vec2(worldCoords[0] * camera.getDistance(), worldCoords[1] * (-camera.getDistance()));

	if (mouseDown != m_mouseDown)
	{
		if (mouseDown)
		{
			Circle* circle = new Circle(m_mousePoint, 1.0f, glm::vec2(0), 1.0f, 0.25f, true);
			m_physicsObjects.push_back(circle);

			if (lastCircle != nullptr)
			{
				m_physicsObjects.push_back(new Spring(circle, lastCircle, 5.0f, 2.0f));
			}

			lastCircle = circle;
		}
		m_mouseDown = mouseDown;
	}

	//TODO: sleep 1000*dt
	Sleep(1000 * dt);

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

	lastCircle = nullptr;

	//Add new physics objects to list
	m_physicsObjects.push_back(new Plane(glm::vec2(0, -5), glm::vec2(0, 1)));
	m_physicsObjects.push_back(new Plane(glm::vec2(0, 35), glm::vec2(0, -1)));
	m_physicsObjects.push_back(new Plane(glm::vec2(-20, 0), glm::vec2(1, 0)));
	m_physicsObjects.push_back(new Plane(glm::vec2(20, 0), glm::vec2(-1, 0)));

	int x = 8, y = 5;

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			m_physicsObjects.push_back(new Box(glm::vec2(i * 3 - 10 + (j % 2 == 0 ? 1 : 0), j * 2 + 3), 2.0f, 1.0f, glm::vec2(0), 2.0f, 0.1f, false));
		}
	}
}
