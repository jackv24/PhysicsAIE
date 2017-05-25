#pragma once

#include <glm\glm\glm.hpp>

class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	void CheckCollisions(PhysicsObject* other);

	enum Type
	{
		CIRCLE,
		PLANE,
		BOX,
		SPRING
	};

	Type type;
};

