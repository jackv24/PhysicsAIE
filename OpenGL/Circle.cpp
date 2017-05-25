#include "stdafx.h"
#include "Circle.h"

#include <aie\Gizmos.h>

Circle::Circle()
{
}

Circle::Circle(glm::vec2 position, float radius, glm::vec2 velocity)
{
	m_position = position;
	m_radius = radius;
	m_velocity = velocity;
}

Circle::~Circle()
{
}

void Circle::Draw()
{
	Gizmos::add2DCircle(m_position, m_radius, 16, glm::vec4(1));
}
