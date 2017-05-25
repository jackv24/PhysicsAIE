#pragma once

#include "RigidBody.h"

class Circle : public RigidBody
{
public:
	Circle();
	Circle(glm::vec2 position, float radius, glm::vec2 velocity);
	~Circle();

	virtual void Draw();

protected:
	float m_radius;
};

