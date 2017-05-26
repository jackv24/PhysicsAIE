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

bool RigidBody::IsFixed() { return m_fixed; }

void RigidBody::ApplyForce(glm::vec2 force)
{
	m_velocity += force/m_mass;
}

void RigidBody::ApplyForce(glm::vec2 force, glm::vec2 position)
{
	m_velocity += force / m_mass;

	m_angularVelocity += (force.y * position.x - force.x * position.y) / moment;
}

void RigidBody::ResolveCollision(RigidBody* other, glm::vec2 contact, glm::vec2* direction)
{
	//Find the vector between their centres, or use the provided direction of force
	glm::vec2 unitDisp = direction ? *direction : glm::normalize(other->GetPosition() - m_position);

	//Get the component along this axis for each object
	glm::vec2 unitParallel(unitDisp.y, -unitDisp.x);

	//Determine the total velocity of the contact points, both linear and rotational
	float r1 = glm::dot(contact - m_position, -unitParallel);
	float r2 = glm::dot(contact - other->GetPosition(), unitParallel);
	float v1 = glm::dot(m_velocity, unitDisp) + r1 * m_angularVelocity;
	float v2 = glm::dot(other->GetVelocity(), unitDisp) + r2*other->GetAngularVelocity();

	//If they're moving closer
	if (v1 > v2)
	{
		//Calculate the effective mass at contact point for each object
		//ie how much the contact point will move due to the force applied
		float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / moment);
		float mass2 = 1.0f / (1.0f / other->m_mass + (r2 * r2) / other->moment);

		glm::vec2 force = (1.0f + m_bounciness) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * unitDisp;

		//Apply equal and opposite forces
		ApplyForce(-force, contact - m_position);
		other->ApplyForce(force, contact - other->GetPosition());
	}
}
