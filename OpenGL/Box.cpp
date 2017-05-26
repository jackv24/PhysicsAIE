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

bool Box::CheckBoxCorners(Box * box, glm::vec2 & contact, int & numContacts, float & pen, glm::vec2 & edgeNormal)
{
	float minX, maxX, minY, maxY;
	float w2 = width / 2, h2 = height / 2;
	int numLocalContacts = 0;

	glm::vec2 localContact;

	bool first = true;

	for (float x = -box->width / 2; x < box->width; x += box->width)
	{
		for (float y = -box->height / 2; y < box->height; y += box->height)
		{
			//Position in worldspace
			glm::vec2 p = box->GetPosition() + x * box->localX + y * box->localY;

			//Position in this box's space
			glm::vec2 p0(glm::dot(p - m_position, localX), glm::dot(p - m_position, localY));

			if (first || p0.x < minX) minX = p0.x;
			if (first || p0.x > maxX) maxX = p0.x;
			if (first || p0.y < minY) minY = p0.y;
			if (first || p0.y > maxY) maxY = p0.y;

			if (p0.x >= -w2 && p0.x <= w2 && p0.y >= -h2 && p0.y <= h2)
			{
				numLocalContacts++;
				localContact += p0;
			}

			first = false;
		}
	}

	if (maxX < -w2 || minX > w2 || maxY < -h2 || minY > h2)
		return false;

	if (numLocalContacts == 0)
		return false;

	bool res = false;

	contact += m_position + (localContact.x * localX + localContact.y * localY) / (float)numLocalContacts;
	numContacts++;

	float pen0 = w2 - minX;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = localX;
		pen = pen0;
		res = true;
	}

	pen0 = maxX + w2;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = -localX;
		pen = pen0;
		res = true;
	}

	pen0 = h2 - minY;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = localY;
		pen = pen0;
		res = true;
	}

	pen0 = maxY + h2;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = -localY;
		pen = pen0;
		res = true;
	}

	return res;
}
