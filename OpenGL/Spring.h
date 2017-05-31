#pragma once

#include "RigidBody.h"

class Spring : public PhysicsObject
{
public:
	Spring(RigidBody* b1, RigidBody* b2, float length, float force);
	~Spring();

	virtual void Update(float deltaTime);
	virtual void Draw();

	RigidBody* body1;
	RigidBody* body2;

	glm::vec2 contact1;
	glm::vec2 contact2;

	float restLength;
	float restoringForce;
};

