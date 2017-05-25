#include "stdafx.h"
#include "Plane.h"

#include <aie\Gizmos.h>

Plane::Plane(glm::vec2 p, glm::vec2 n)
{
	position = p;
	normal = glm::normalize(n);

	type = PLANE;
}

Plane::~Plane()
{
}

void Plane::Update(float deltaTime)
{
}

void Plane::Draw()
{
	glm::vec2 perp = glm::vec2(normal.y, -normal.x);

	glm::vec2 p1 = position - 100.0f * perp;
	glm::vec2 p2 = position + 100.0f * perp;

	Gizmos::add2DLine(p1, p2, glm::vec4(1));
}
