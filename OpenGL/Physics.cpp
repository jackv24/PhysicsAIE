#include "stdafx.h"
#include "Physics.h"

#include "Circle.h"
#include "Plane.h"

void Physics::CirclePlaneCollision(Circle * circle, Plane * plane)
{
	//Perpendicular distance of the circle to the plane
	float d = glm::dot((circle->GetPosition() - plane->position), plane->normal);

	//Velocity of the circle in the perpendicular direction of the plane
	float v = glm::dot(circle->GetVelocity(), plane->normal);

	float radius = circle->GetRadius();

	//Collision test
	if ((d > 0 && d < radius && v < 0) || (d < 0 && d > -radius && v > 0))
	{
		glm::vec2 force = -circle->GetMass() * (v*plane->normal) * (1 + circle->GetBounciness());

		circle->ApplyForce(force);
	}
}
