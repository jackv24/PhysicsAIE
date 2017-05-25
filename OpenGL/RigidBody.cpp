#include "stdafx.h"
#include "RigidBody.h"

glm::vec2 gravity = glm::vec2(0, -9.8f);

RigidBody::RigidBody()
{
}

RigidBody::RigidBody(glm::vec2 position, glm::vec2 velocity)
{
	m_position = position;
	m_velocity = velocity;
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