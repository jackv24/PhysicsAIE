#include "stdafx.h"
#include "Circle.h"

#include <aie\Gizmos.h>

Circle::Circle()
{
	m_position = glm::vec2(0);
	m_radius = 1.0f;
	m_velocity = glm::vec2(0);
	m_mass = 1.0f;
	m_bounciness = 0.0f;

	type = CIRCLE;

	moment = 0.5f * m_mass * m_radius * m_radius;
}

Circle::Circle(glm::vec2 position, float radius, glm::vec2 velocity, float mass, float bounciness)
{
	m_position = position;
	m_radius = radius;
	m_velocity = velocity;
	m_mass = mass;
	m_bounciness = bounciness;

	type = CIRCLE;

	moment = 0.5f * m_mass * m_radius * m_radius;
}

Circle::~Circle()
{
}

void Circle::Draw()
{
	Gizmos::add2DCircle(m_position, m_radius, 16, glm::vec4(1.0f, 0.25f, 0.25f, 1.0f));
	Gizmos::add2DCircle(m_position + m_radius*0.5f*localX, m_radius*0.2f, 16, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

float Circle::GetRadius() { return m_radius; }
