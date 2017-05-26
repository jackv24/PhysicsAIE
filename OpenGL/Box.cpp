#include "stdafx.h"
#include "Box.h"

#include <aie\Gizmos.h>

Box::Box()
{
	m_position = glm::vec2(0);
	width = 1.0f;
	height = 1.0f;

	m_velocity = glm::vec2(0);
	m_mass = 1.0f;
	m_bounciness = 0.0f;

	type = BOX;

	moment = 1.0f / 12.0f * m_mass * width * height;
}

Box::Box(glm::vec2 position, float w, float h, glm::vec2 velocity, float mass, float bounciness)
{
	m_position = position;
	width = w;
	height = h;

	m_velocity = velocity;
	m_mass = mass;
	m_bounciness = bounciness;

	type = BOX;

	moment = 1.0f / 12.0f * m_mass * width * height;

	m_rotation = 25.0f;
}

Box::~Box()
{
}

void Box::Draw()
{
	glm::vec2 p1 = m_position - localX * width / 2.0f - localY * height / 2.0f;
	glm::vec2 p2 = m_position + localX * width / 2.0f - localY * height / 2.0f;
	glm::vec2 p3 = m_position - localX * width / 2.0f + localY * height / 2.0f;
	glm::vec2 p4 = m_position + localX * width / 2.0f + localY * height / 2.0f;

	Gizmos::add2DTri(p1, p2, p4, glm::vec4(0.25f, 1.0f, 0.75f, 1.0f));
	Gizmos::add2DTri(p1, p4, p3, glm::vec4(0.25f, 1.0f, 0.75f, 1.0f));
}
