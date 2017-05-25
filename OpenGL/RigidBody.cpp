#include "stdafx.h"
#include "RigidBody.h"

static glm::vec2 gravity = glm::vec2(0, -9.8f);

RigidBody::RigidBody()
{
	m_position = glm::vec2(0);
	m_velocity = glm::vec2(0);
	m_mass = 1.0f;
}

RigidBody::RigidBody(glm::vec2 position, glm::vec2 velocity, float mass)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update(float deltaTime)
{
	//Apply gravity to velocity over time
	m_velocity += gravity * deltaTime;

	//Apply velocity to position
	m_position += m_velocity * deltaTime;
}

void RigidBody::SetPosition(glm::vec2 position) { m_position = position; }
void RigidBody::SetVelocity(glm::vec2 velocity) { m_velocity = velocity; }

glm::vec2 RigidBody::GetPosition() { return m_position; }
glm::vec2 RigidBody::GetVelocity() { return m_velocity; }
float RigidBody::GetMass() { return m_mass; }
float RigidBody::GetBounciness() { return m_bounciness; }

void RigidBody::ApplyForce(glm::vec2 force)
{
	m_velocity += force;
}
