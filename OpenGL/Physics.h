#pragma once

class Circle;
class Plane;
class Box;

class Physics
{
public:
	static void CirclePlaneCollision(Circle* circle, Plane* plane);
	static void BoxPlaneCollision(Box* box, Plane* plane);
};

