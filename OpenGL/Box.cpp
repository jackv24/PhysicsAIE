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

void Box::CheckBoxCorners(Box * box, glm::vec2 & contact, int & numContacts, float & pen, glm::vec2 & edgeNormal, glm::vec2& contactForce)
{
	float penetration = 0;
	for (float x = -box->width / 2; x < box->width; x += box->width)
	{
		for (float y = -box->height / 2; y < box->height; y += box->height)
		{
			glm::vec2 p = box->GetPosition() + x*box->localX + y*box->localY; // pos in worldspace
			glm::vec2 p0(glm::dot(p - m_position, localX), glm::dot(p - m_position, localY));
			float w2 = width / 2, h2 = height / 2;
			if (p0.y < h2 && p0.y > -h2)
			{
				if (p0.x > 0 && p0.x < w2)
				{
					numContacts++;
					contact += m_position + w2 * localX + p0.y * localY;
					edgeNormal = localX;
					penetration = w2 - p0.x;
				}
				if (p0.x < 0 && p0.x > -w2)
				{
					numContacts++;
					contact += m_position - w2 * localX + p0.y * localY;
					edgeNormal = -localX;
					penetration = w2 + p0.x;
				}
			}
			if (p0.x < w2 && p0.x > -w2)
			{
				if (p0.y > 0 && p0.y < h2)
				{
					numContacts++;
					contact += m_position + p0.x * localX + h2 * localY;
					float pen0 = h2 - p0.y;
					if (pen0 < penetration || penetration == 0)
					{
						penetration = pen0;
						edgeNormal = localY;
					}
				}
				if (p0.y < 0 && p0.y > -h2)
				{
					numContacts++;
					contact += m_position + p0.x * localX - h2 * localY;
					float pen0 = h2 + p0.y;
					if (pen0 < penetration || penetration == 0)
					{
						penetration = pen0;
						edgeNormal = -localY;
					}
				}
			}
		}
	}
	contactForce = penetration*edgeNormal;
}
