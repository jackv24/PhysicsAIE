#include "stdafx.h"
#include "Circle.h"

#include <aie\Gizmos.h>

Circle::Circle()
{
	type = CIRCLE;
}

Circle::Circle(glm::vec2 position, float radius, glm::vec2 velocity, float mass, float bounciness)
{
	m_position = position;
	m_radius = radius;
	m_velocity = velocity;
	m_mass = mass;
	m_bounciness = bounciness;

	type = CIRCLE;
}

Circle::~Circle()
{
}

void Circle::Draw()
{
	Gizmos::add2DCircle(m_position, m_radius, 16, glm::vec4(1));
}

float Circle::GetRadius() { return m_radius; }
