#pragma once
#include <vector>

using std::vector;

struct Point
{
	double X;
	double Y;

	Point()
	{
		X = 0;
		Y = 0;
	}
	Point(double x, double y)
	{
		X = x;
		Y = y;
	}
};

struct Vector
{
	double X;
	double Y;
	double length;

	Vector()
	{
		X = 0;
		Y = 0;
	}
	Vector(double x, double y)
	{
		X = x;
		Y = y;
	}
};

struct Line
{
	double X1;
	double Y1;
	double X2;
	double Y2;

	Line() {}
	Line(double x1, double y1, double x2, double y2)
	{
		X1 = x1;
		Y1 = y1;
		X2 = x2;
		Y2 = Y2;
	}
	Line(Point p1, Point p2)
	{
		X1 = p1.X;
		Y1 = p1.Y;
		X2 = p2.X;
		Y2 = p2.Y;
	}

};

struct Dummy
{
	int realPos;
	int offset;
	Dummy() {};
	Dummy(int d)
	{
		realPos = d;
		offset = d;
	}
};


enum StrategyMode
{
	defense,
	attack
};


enum AxisMode
{
	forwardDefense,
	backwardDefense,
	forwardShoot,
	backwardShoot,
	raised
};


enum BallVectorMode
{
	known,
	unknown,
	initial
};

struct Axis
{
	int desiredDisplacement;
	int realDisplacement;
	int X;
	vector<Dummy> dummies;
	AxisMode mode;
	Axis() {}
	int intersectionY;
	int desiredIntercept;

	double acceleration;
	double speed;
	double angularSpeed;
	double angle;
	double xDisplacement;
	int y_min;
	int y_max;

	Axis(vector<int> d, int x, int ymin, int ymax)
	{
		desiredIntercept = 0;
		intersectionY = 5000;
		X = x;
		for (int i = 0; i < d.size(); i++)
		{
			dummies.push_back(Dummy(d[i]));
		}
		//dummies = d;
		//maxDisplacement = maxd;

		y_max = ymax;
		y_min = ymin;

		angle = 0;
		xDisplacement = 0;
		realDisplacement = 0;
		desiredDisplacement = 0;
		mode = forwardDefense;
		speed = 0;
		acceleration = 0;
		angularSpeed = 0;
	}

};