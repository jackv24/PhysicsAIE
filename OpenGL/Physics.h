#pragma once

class Circle;
class Plane;
class Box;

class Physics
{
public:
	static void CirclePlaneCollision(Circle* circle, Plane* plane);
	static void CircleCircleCollision(Circle* circle1, Circle* circle2);

	static void BoxPlaneCollision(Box* box, Plane* plane);
	static void BoxCircleCollision(Box* box, Circle* circle);
	static void BoxBoxCollision(Box* box1, Box* box2);
};

