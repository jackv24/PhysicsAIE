#pragma once

#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	RigidBody();
	RigidBody(glm::vec2 position, glm::vec2 velocity, float mass, float bounciness);
	~RigidBody();

	virtual void Update(float deltaTime);

	void SetPosition(glm::vec2 position);
	void SetVelocity(glm::vec2 velocity);

	glm::vec2 GetPosition();
	glm::vec2 GetVelocity();
	float GetRotation();
	float GetAngularVelocity();
	float GetMass();
	float GetBounciness();

	void ApplyForce(glm::vec2 force);
	void ApplyForce(glm::vec2 force, glm::vec2 position);

	void ResolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* direction);

	glm::vec2 localX;
	glm::vec2 localY;

	float moment = 0.0f;

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;

	float m_rotation;
	float m_angularVelocity;

	float m_mass;
	float m_bounciness = 0.0f;
};

