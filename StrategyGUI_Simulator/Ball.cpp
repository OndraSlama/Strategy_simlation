#include "Ball.h"


Ball::Ball()
{
	center = Point(-100, 0);
	radius = 175;
	vector = Vector();
	speed = 0;
	state = initial;
	framesSinceLastBounce = 0;
}

Ball::~Ball()
{
}


Ball::Ball(int r, Vector v, Point c, int s)
{
	center = c;
	vector = v;
	radius = r;
	speed = s;
	state = initial;
	framesSinceLastBounce = 0;
}