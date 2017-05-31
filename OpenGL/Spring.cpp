#include "stdafx.h"
#include "Spring.h"

#include <aie\Gizmos.h>

Spring::Spring(RigidBody* b1, RigidBody* b2, float length, float force)
{
	body1 = b1;
	body2 = b2;
	restLength = length;
	restoringForce = force;

	type = SPRING;
}

Spring::~Spring()
{
}

void Spring::Update(float deltaTime)
{
	glm::vec2 p2 = body2->ToWorld(contact2);
	glm::vec2 p1 = body1->ToWorld(contact1);
	glm::vec2 dist = p2 - p1;

	float len = sqrtf(dist.x*dist.x + dist.y*dist.y);

	//Apply damping
	glm::vec2 dv = body2->GetVelocity() - body1->GetVelocity();

	float damping = 0.1f;
	glm::vec2 force = dist * restoringForce * (restLength - len) - damping * dv;

	body1->ApplyForce(-force * deltaTime, p1 - body1->GetPosition());
	body2->ApplyForce(force * deltaTime, p2 - body2->GetPosition());
}

void Spring::Draw()
{
	Gizmos::add2DLine(body1->ToWorld(contact1), body2->ToWorld(contact2), glm::vec4(1));
}
