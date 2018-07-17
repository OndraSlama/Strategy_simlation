#include "BaseStrategy.h"


BaseStrategy::BaseStrategy()
{
	balls[0] = Ball();
	balls[1] = Ball();
	balls[2] = Ball();

	cycleLength = 2;
	cyclesSinceLastCameraInput = 0;
	cyclesSinceAttackBeginning = 0;

	StrategyMode mode = defense;

	DummyX = 100;
	DummyY = 200;

	goalWidth = 1065;

	minSpeedLimit = 3;

	field[0] = Line(0, -3515, 0, 3515);			//left
	field[1] = Line(0, 3515, 12100, 3515);		//top
	field[2] = Line(12100, 3515, 12100, -3515); //right
	field[3] = Line(12100, -3515, 0, -3515);		//bottom

	SetupAxis();



}


BaseStrategy::~BaseStrategy()
{
}

Line BaseStrategy::TrajectoryUntilBounce(Ball& b, bool& last)
{
	Point intersection;

	// check field boundaries
	if (b.vector.X > 0)
	{
		if (b.vector.Y > 0) //X>0, Y>0 //right, up
		{
			intersection = Point(12100 - ball.radius, ((12100 - ball.radius - b.center.X) / b.vector.X)*b.vector.Y + b.center.Y); //right
			if (intersection.Y > 3515 - ball.radius) // wrong point 
			{
				intersection = Point(((3515 - ball.radius - b.center.Y) / b.vector.Y)*b.vector.X + b.center.X, 3515 - ball.radius); //top
				b.vector.Y *= -1;
			}
			else
			{
				b.vector.X *= -1;
			}
		}
		else //X>0, Y<0 //right, down
		{
			intersection = Point(12100 - ball.radius, ((12100 - ball.radius - b.center.X) / b.vector.X)*b.vector.Y + b.center.Y); //right
			if (intersection.Y < -3515) // wrong point 
			{
				intersection = Point(((-3515 + ball.radius - b.center.Y) / b.vector.Y)*b.vector.X + b.center.X, -3515 + ball.radius); //bottom
				b.vector.Y *= -1;
			}
			else
			{
				b.vector.X *= -1;
			}
		}
	}
	else //X<0
	{
		if (b.vector.Y > 0) //X<0, Y>0 //left, up
		{
			intersection = Point(0 + ball.radius, ((0 + ball.radius - b.center.X) / b.vector.X)*b.vector.Y + b.center.Y); //left
			if (intersection.Y > 3515 - ball.radius) // wrong point 
			{
				intersection = Point(((3515 - ball.radius - b.center.Y) / b.vector.Y)*b.vector.X + b.center.X, 3515 - ball.radius); //top
				b.vector.Y *= -1;
			}
			else
			{
				b.vector.X *= -1;
			}
		}
		else //X<0, Y<0  //left, down
		{
			intersection = Point(0 + ball.radius, ((0 + ball.radius - b.center.X) / b.vector.X)*b.vector.Y + b.center.Y); //left
			if (intersection.Y < -3515 + ball.radius) // wrong point 
			{
				intersection = Point(((-3515 + ball.radius - b.center.Y) / b.vector.Y)*b.vector.X + b.center.X, -3515 + ball.radius); //bottom
				b.vector.Y *= -1;
			}
			else
			{
				b.vector.X *= -1;
			}
		}
	}

	if (intersection.X == ball.radius || intersection.X == 12100 - ball.radius)
	{
		last = true;
	}
	Point o = b.center;
	b.center = intersection;
	return Line(o, intersection);
}



void BaseStrategy::Reset()
{
	trajectory.clear();

	SetupAxis();
	cyclesSinceAttackBeginning = 0;

}

void BaseStrategy::SetupAxis()
{
	vector<int> dummies;
	dummies.push_back(0);
	axes[0] = Axis(dummies, 800, -920, 805);
	dummies.clear();

	dummies.push_back(-1190);
	dummies.push_back(1190);
	axes[1] = Axis(dummies, 2300, -970, 1070);
	dummies.clear();

	dummies.push_back(-2380);
	dummies.push_back(-1190);
	dummies.push_back(0);
	dummies.push_back(1190);
	dummies.push_back(2380);
	axes[2] = Axis(dummies, 5300, -540, 560);
	dummies.clear();

	dummies.push_back(-2080);
	dummies.push_back(0);
	dummies.push_back(2080);
	axes[3] = Axis(dummies, 8300, -800, 870);
	dummies.clear();
}

void BaseStrategy::CalculateTrajectory()
{
	// setup
	bool last = false;
	Ball curball = ball;
	Line currentLine;
	trajectory.clear();


	// if (ball.speed > minSpeedLimit && abs(ball.vector.Y) < 0.9)
	{
		while (!last && trajectory.size() < 10)
		{
			currentLine = TrajectoryUntilBounce(curball, last);
			trajectory.push_back(currentLine);
		}
	}
}

void BaseStrategy::CalculateAxesIntersections()
{
	// erase all
	for (int j = 0; j < 4; j++)
	{
		axes[j].intersectionY = -10000;
	}

	// axes crossings
	for (int i = 0; i < trajectory.size(); i++)
	{

		for (int j = 0; j < 4; j++)
		{
			if (trajectory[i].X1 > axes[j].X && axes[j].X > trajectory[i].X2)	// doleva
			{
				if (trajectory[i].X2 != 0 && trajectory[i].X1 != 0)
				{

					axes[j].intersectionY = (axes[j].X + axes[j].xDisplacement + DummyX / 2 - (trajectory[i].X1 - ball.radius)) / float((trajectory[i].X2 - trajectory[i].X1))*(trajectory[i].Y2 - trajectory[i].Y1) + trajectory[i].Y1;
				}
				else
				{
					axes[j].intersectionY = 0;
				}
			}
			else if (trajectory[i].X2 > axes[j].X && axes[j].X > trajectory[i].X1) // doprava
			{
				if (trajectory[i].X2 != 0 && trajectory[i].X1 != 0)
				{
					axes[j].intersectionY = (axes[j].X + axes[j].xDisplacement - DummyX / 2 - (trajectory[i].X1 + ball.radius)) / float((trajectory[i].X2 - trajectory[i].X1))*(trajectory[i].Y2 - trajectory[i].Y1) + trajectory[i].Y1;
				}
				else
				{
					axes[j].intersectionY = 0;
				}
			}
		}
	}
}
