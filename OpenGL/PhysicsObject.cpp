#include "stdafx.h"
#include "PhysicsObject.h"

#include "Physics.h"

PhysicsObject::PhysicsObject()
{
}
PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::CheckCollisions(PhysicsObject * other)
{
	if (type == CIRCLE && other->type == PLANE)
		Physics::CirclePlaneCollision((Circle*)this, (Plane*)other);
	else if (type == PLANE && other->type == CIRCLE)
		Physics::CirclePlaneCollision((Circle*)other, (Plane*)this);
	
	else if (type == BOX && other->type == PLANE)
		Physics::BoxPlaneCollision((Box*)this, (Plane*)other);
	else if (type == PLANE && other->type == BOX)
		Physics::BoxPlaneCollision((Box*)other, (Plane*)this);
}
