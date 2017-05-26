#include "stdafx.h"
#include "Physics.h"

#include "Circle.h"
#include "Plane.h"
#include "Box.h"

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
		circle->SetPosition(circle->GetPosition() - plane->normal * (d - radius));

		glm::vec2 force = -circle->GetMass() * (v*plane->normal) * (1 + circle->GetBounciness());
		circle->ApplyForce(force);
	}
}

void Physics::BoxPlaneCollision(Box * box, Plane * plane)
{
	int numContacts = 0;
	glm::vec2 contact(0, 0);
	float contactV = 0;
	float radius = 0.5f * std::fminf(box->width, box->height);

	//Which side is the centre of mass on?
	float comeFromPlane = glm::dot(box->GetPosition() - plane->position, plane->normal);
	float penetration = 0;

	//Collision test on all four corners
	for (float x = -box->width / 2; x < box->width; x += box->width)
	{
		for (float y = -box->height / 2; y < box->height; y += box->height)
		{
			//Get position of corner in world space
			glm::vec2 p = box->GetPosition() + x*box->localX + y * box->localY;
			float distFromPlane = glm::dot(p - plane->position, plane->normal);

			//Total velocity of the point
			float velocityIntoPlane = glm::dot(box->GetVelocity() + box->GetAngularVelocity() *(-y*box->localX + x*box->localY), plane->normal);
		
			//If this corner is on the opposite side of the centre of mass
			//and moving further in, resolve the collision
			if ((distFromPlane > 0 && comeFromPlane < 0 && velocityIntoPlane > 0)
				|| (distFromPlane < 0 && comeFromPlane > 0 && velocityIntoPlane < 0))
			{
				numContacts++;
				contact += p;
				contactV += velocityIntoPlane;

				if (comeFromPlane >= 0)
				{
					penetration = std::fminf(penetration, distFromPlane);
				}
				else
				{
					penetration = fmaxf(penetration, distFromPlane);
				}
			}

		}
	}

	box->SetPosition(box->GetPosition() - penetration * plane->normal);

	//If a corner has hit (typically only two can contact)
	if (numContacts > 0)
	{
		//Get average collision velocity into plane
		float collisionV = contactV / (float)numContacts;

		//Get the acceleration required to stop (bounciness = 0) or 
		//reverse (bounciness = 1) the average velocity into the plane
		glm::vec2 acceleration = -plane->normal * ((1.0f + box->GetBounciness()) * collisionV);

		//Get the average position at which we'll apply the force
		glm::vec2 localContact = (contact / (float)numContacts) - box->GetPosition();

		//The perpendicular distance to apply the force at
		float r = glm::dot(localContact, glm::vec2(plane->normal.y, -plane->normal.x));

		//Work out the effective mass - the combination of moment of inertia and mass
		float mass = 1.0f / (1.0f / box->GetMass() + (r * r) / box->moment);

		box->ApplyForce(acceleration*mass, localContact);
	}
}

void Physics::CircleCircleCollision(Circle * circle1, Circle * circle2)
{
	glm::vec2 disp = circle2->GetPosition() - circle1->GetPosition();

	float d = sqrtf(disp.x * disp.x + disp.y * disp.y);

	if (d > 0 && d < circle1->GetRadius() + circle2->GetRadius())
	{
		glm::vec2 contactForce = 0.5f * (d - (circle1->GetRadius() + circle2->GetRadius())) * disp / d;
		circle1->SetPosition(circle1->GetPosition() + contactForce);
		circle2->SetPosition(circle2->GetPosition() - contactForce);

		glm::vec2 contact = circle1->GetPosition() + glm::normalize(circle2->GetPosition() - circle1->GetPosition()) * circle1->GetRadius();

		circle1->ResolveCollision(circle2, contact, nullptr);
	}
}

void Physics::BoxCircleCollision(Box * box, Circle * circle)
{
	glm::vec2 circlePos = circle->GetPosition() - box->GetPosition();
	float w2 = box->width / 2;
	float h2 = box->height / 2;

	int numContacts = 0;

	//Contact is in box space
	glm::vec2 contact(0, 0);

	//Check corners
	for (float x = w2; x < box->width; x += box->width)
	{
		for (float y = -h2; y < box->height; y += box->height)
		{
			glm::vec2 p = x * box->localX + y * box->localY;
			glm::vec2 dp = p - circlePos;

			if (dp.x * dp.x + dp.y * dp.y < circle->GetRadius() * circle->GetRadius())
			{
				numContacts++;
				contact += glm::vec2(x, y);
			}
		}
	}

	//Check edges
	glm::vec2* direction = NULL;

	//Get the local position of the circle centre
	glm::vec2 localPos(glm::dot(box->localX, circlePos), glm::dot(box->localY, circlePos));

	if (localPos.y < h2 && localPos.y > -h2)
	{
		if (localPos.x > 0 && localPos.x < w2 + circle->GetRadius())
		{
			numContacts++;
			contact += glm::vec2(w2, localPos.y);
			direction = new glm::vec2(box->localX);
		}

		if (localPos.x < 0 && localPos.x > -(w2 + circle->GetRadius()))
		{
			numContacts++;
			contact += glm::vec2(-w2, localPos.y);
			direction = new glm::vec2(-box->localX);
		}
	}

	if (localPos.x < w2 && localPos.x > -w2)
	{
		if (localPos.y > 0 && localPos.y < h2 + circle->GetRadius())
		{
			numContacts++;
			contact += glm::vec2(localPos.x, h2);
			direction = new glm::vec2(box->localY);
		}
		if (localPos.y < 0 && localPos.y > -(h2 + circle->GetRadius()))
		{
			numContacts++;
			contact += glm::vec2(localPos.x, -h2);
			direction = new glm::vec2(-box->localY);
		}
	}

	if (numContacts > 0)
	{
		//Average, and convert back into world coords
		contact = box->GetPosition() + (1.0f / numContacts) * (box->localX*contact.x + box->localY*contact.y);
		box->ResolveCollision(circle, contact, direction);
	}

	delete direction;
}

void Physics::BoxBoxCollision(Box * box1, Box * box2)
{
	glm::vec2 boxPos = box2->GetPosition() - box1->GetPosition();

	glm::vec2 n1, n2;
	glm::vec2 contact;
	float pen = 0;
	int numContacts = 0;

	glm::vec2 cf1, cf2;

	box1->CheckBoxCorners(box2, contact, numContacts, pen, n1, cf1);
	box2->CheckBoxCorners(box1, contact, numContacts, pen, n2, cf2);

	//Subtract because they're facing different directions
	glm::vec2 edgeNormal = glm::normalize(n1 - n2);

	glm::vec2 contactForce = 0.5f * (cf1 - cf2);
	box1->SetPosition(box1->GetPosition() - contactForce);
	box2->SetPosition(box2->GetPosition() + contactForce);

	if (pen > 0)
	{
		box1->ResolveCollision(box2, contact / float(numContacts), &edgeNormal);

		float numDynamic = (box1->IsFixed() ? 0 : 1) + (box2->IsFixed() ? 0 : 1);

		if (numDynamic > 0)
		{
			glm::vec2 contactForce = edgeNormal * pen / numDynamic;

			if (!box1->IsFixed())
				box1->SetPosition(box1->GetPosition() - contactForce);
			
			if (!box2->IsFixed())
				box2->SetPosition(box2->GetPosition() + contactForce);
		}
	}
}
