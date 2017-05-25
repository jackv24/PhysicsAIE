#pragma once

#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	RigidBody();
	RigidBody(glm::vec2 position, glm::vec2 velocity, float mass);
	~RigidBody();

	virtual void Update(float deltaTime);

	void SetPosition(glm::vec2 position);
	void SetVelocity(glm::vec2 velocity);

	glm::vec2 GetPosition();
	glm::vec2 GetVelocity();
	float GetMass();
	float GetBounciness();

	void ApplyForce(glm::vec2 force);

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_bounciness = 0.0f;
};

