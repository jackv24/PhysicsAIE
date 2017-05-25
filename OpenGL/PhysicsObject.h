#pragma once

#include <glm\glm\glm.hpp>

class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

