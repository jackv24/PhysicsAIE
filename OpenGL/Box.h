#pragma once

#include "RigidBody.h"

class Box : public RigidBody
{
public:
	Box();
	Box(glm::vec2 position, float w, float h, glm::vec2 velocity, float mass, float bounciness);
	~Box();

	virtual void Draw();

	bool CheckBoxCorners(Box* box, glm::vec2& contact, int& numContacts, float &pen, glm::vec2& edgeNormal);

	float width;
	float height;
};

