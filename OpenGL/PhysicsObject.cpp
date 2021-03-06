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

	else if (type == CIRCLE && other->type == CIRCLE)
		Physics::CircleCircleCollision((Circle*)this, (Circle*)other);

	else if (type == BOX && other->type == CIRCLE)
		Physics::BoxCircleCollision((Box*)this, (Circle*)other);
	else if (type == CIRCLE && other->type == BOX)
		Physics::BoxCircleCollision((Box*)other, (Circle*)this);

	else if (type == BOX && other->type == BOX)
		Physics::BoxBoxCollision((Box*)this, (Box*)other);
}
