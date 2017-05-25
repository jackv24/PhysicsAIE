#pragma once

#include "RigidBody.h"

class Circle : public RigidBody
{
public:
	Circle();
	Circle(glm::vec2 position, float radius, glm::vec2 velocity, float mass, float bounciness);
	~Circle();

	virtual void Draw();

	float GetRadius();

private:
	float m_radius;
};

