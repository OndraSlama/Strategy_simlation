#pragma once
#include "Structs.h"

class Ball
{
public:
	Ball();
	Ball(int, Vector, Point, int);
	~Ball();

	// properties
	Point center;
	Point lastCenter;
	Vector vector;
	int radius;
	double speed;
	BallVectorMode state;
	int framesSinceLastBounce;
};