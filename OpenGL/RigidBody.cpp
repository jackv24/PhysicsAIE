#include "stdafx.h"
#include "RigidBody.h"

static glm::vec2 gravity = glm::vec2(0, -9.8f);

RigidBody::RigidBody()
{
	m_position = glm::vec2(0);
	m_velocity = glm::vec2(0);
	m_mass = 1.0f;
	m_bounciness = 0;

	m_rotation = 0;
	m_angularVelocity = 0;

	localX = glm::vec2(1, 0);
	localY = glm::vec2(0, 1);
}

RigidBody::RigidBody(glm::vec2 position, glm::vec2 velocity, float mass, float bounciness)
{
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_bounciness = bounciness;

	m_rotation = 0;
	m_angularVelocity = 0;

	localX = glm::vec2(1, 0);
	localY = glm::vec2(0, 1);
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update(float deltaTime)
{
	//Apply velocity to position
	m_position += m_velocity * deltaTime;

	//Apply gravity to velocity over time
	m_velocity += gravity * deltaTime;

	//Rotation and angular velocity
	m_rotation += m_angularVelocity * deltaTime;

	//Store local axes
	float cs = cosf(m_rotation);
	float sn = sinf(m_rotation);
	localX = glm::vec2(cs, sn);
	localY = glm::vec2(-sn, cs);
}

void RigidBody::SetPosition(glm::vec2 position) { m_position = position; }
void RigidBody::SetVelocity(glm::vec2 velocity) { m_velocity = velocity; }

glm::vec2 RigidBody::GetPosition() { return m_position; }
glm::vec2 RigidBody::GetVelocity() { return m_velocity; }
float RigidBody::GetRotation() { return m_rotation; }
float RigidBody::GetAngularVelocity() { return m_angularVelocity; }
float RigidBody::GetMass() { return m_mass; }
float RigidBody::GetBounciness() { return m_bounciness; }

void RigidBody::ApplyForce(glm::vec2 force)
{
	m_velocity += force/m_mass;
}

void RigidBody::ApplyForce(glm::vec2 force, glm::vec2 position)
{
	m_velocity += force / m_mass;

	m_angularVelocity += (force.y * position.x - force.x * position.y) / moment;
}
