#pragma once

#include "PhysicsObject.h"

class Plane : public PhysicsObject
{
public:
	Plane(glm::vec2 p, glm::vec2 n);
	~Plane();

	virtual void Update(float deltaTime);
	virtual void Draw();

	glm::vec2 position;
	glm::vec2 normal;
};

