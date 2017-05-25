#pragma once

#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	RigidBody();
	RigidBody(glm::vec2 position, glm::vec2 velocity);
	~RigidBody();

	virtual void Update(float deltaTime);

	void SetPosition(glm::vec2 position);
	void SetVelocity(glm::vec2 velocity);

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
};

