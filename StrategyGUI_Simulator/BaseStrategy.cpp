#include "BaseStrategy.h"


BaseStrategy::BaseStrategy()
{
	balls[0] = Ball();
	balls[1] = Ball();
	balls[2] = Ball();
	
	cameraTolerance = 0.53;

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
	// Red player axes
	vector<int> dummies;
	dummies.push_back(0);
	axes[0] = Axis(dummies, 800, -920, 805);
	opponentAxes[0] = Axis(dummies, 12100 - 800, -920, 805);
	dummies.clear();

	dummies.push_back(-1190);
	dummies.push_back(1190);
	axes[1] = Axis(dummies, 2300, -970, 1070);
	opponentAxes[1] = Axis(dummies, 12100 - 2300, -970, 1070);
	dummies.clear();

	dummies.push_back(-2380);
	dummies.push_back(-1190);
	dummies.push_back(0);
	dummies.push_back(1190);
	dummies.push_back(2380);
	axes[2] = Axis(dummies, 5300, -540, 560);
	opponentAxes[2] = Axis(dummies, 12100 - 5300, -540, 560);
	dummies.clear();

	dummies.push_back(-2080);
	dummies.push_back(0);
	dummies.push_back(2080);
	axes[3] = Axis(dummies, 8300, -800, 870);
	opponentAxes[3] = Axis(dummies, 12100 - 8300, -800, 870);
	dummies.clear();
}

void BaseStrategy::CalculateTrajectory()
{
	// setup
	bool last = false;
	Ball curball = ball;
	Line currentLine;
	trajectory.clear();

	while (!last && trajectory.size() < 10)
	{
		currentLine = TrajectoryUntilBounce(curball, last);
		trajectory.push_back(currentLine);
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

					axes[j].intersectionY = (axes[j].X + (axes[j].mode == raised ? 0 : axes[j].xDisplacement) + DummyX / 2 - (trajectory[i].X1 - ball.radius)) / float((trajectory[i].X2 - trajectory[i].X1))*(trajectory[i].Y2 - trajectory[i].Y1) + trajectory[i].Y1;
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
					axes[j].intersectionY = (axes[j].X + (axes[j].mode == raised ? 0 : axes[j].xDisplacement) - DummyX / 2 - (trajectory[i].X1 + ball.radius)) / float((trajectory[i].X2 - trajectory[i].X1))*(trajectory[i].Y2 - trajectory[i].Y1) + trajectory[i].Y1;
				}
				else
				{
					axes[j].intersectionY = 0;
				}
			}
		}
	}
}

void BaseStrategy::CameraInput(int x, int y)
{

	balls[2] = balls[1];
	balls[1] = balls[0];
	balls[0].center.X = x;
	balls[0].center.Y = y;

	ball.center = balls[0].center;

	// Update ball
	SetBall(x - balls[1].center.X, y - balls[1].center.Y);

	// Update axes
	for (int i = 0; i < 4; i++)	{
		for (int j = 0; j < axes[i].dummies.size(); j++){
			axes[i].dummies[j].realPos = axes[i].realDisplacement + axes[i].dummies[j].offset;
		}

		for (int j = 0; j < opponentAxes[i].dummies.size(); j++) {
			opponentAxes[i].dummies[j].realPos = opponentAxes[i].realDisplacement + opponentAxes[i].dummies[j].offset;
		}
		
	}

	// mam minuly smer
	if (ball.state == known)
	{
		float auxLength = sqrt((x - balls[1].center.X)*(x - balls[1].center.X) + (y - balls[1].center.Y)*(y - balls[1].center.Y));
		float auxX = (x - balls[1].center.X) / auxLength;
		float auxY = (y - balls[1].center.Y) / auxLength;

		float a2 = atan2(auxY, auxX);
		float a1 = atan2(balls[1].vector.Y, balls[1].vector.X);
		float sign = a1 > a2 ? 1 : -1;
		float angle = a1 - a2;
		float K = -sign * 3.14159 * 2;
		angle = (abs(K + angle) < abs(angle)) ? K + angle : angle;

		// pokracuje mic v trajektorii?
		if (abs(angle) < cameraTolerance && ball.speed > minSpeedLimit)
		{
			ball.state = known;
		}

		else // mohl byt odraz
		{
			ball.state = unknown;
			balls[0].state = unknown;
			balls[1].state = unknown;
			balls[2].state = unknown;

		}
	}
	else // unknown or initial
	{
		if (ball.state == unknown && ball.speed > minSpeedLimit)
		{
			ball.state = known;
			balls[0].state = known;

		}
		else // initial
		{
			ball.state = unknown;
			balls[0].state = unknown;
		}

	}

	if (ball.speed < minSpeedLimit || abs(ball.vector.Y) > 0.9)
	{
		ball.state = unknown;
		balls[0].state = unknown;
		balls[1].state = unknown;
		balls[2].state = unknown;
	}


	if (ball.state == known)
	{
		CalculateTrajectory(); // jen po X krajni
		CalculateAxesIntersections();
	}
	else
	{
		trajectory.clear();
	}


	// musi byt na konci, pouzivam v setball aktualni hodnotu
	cyclesSinceLastCameraInput = 0;

}

// x difference, y difference
void BaseStrategy::SetBall(double x, double y)
{
	if (x == 0 && y == 0)
	{
		balls[0].vector.length = 0;
		balls[0].vector.X = 0;
		balls[0].vector.Y = 0;
		balls[0].speed = 0;
		
		ball.vector.length = 0;
		ball.vector.X = 0;
		ball.vector.Y = 0;
		ball.speed = 0;

		ball.lastCenter = ball.center;

		return;
	}

	balls[0].vector.length = sqrt(x*x + y * y);

	balls[0].vector.X = x / balls[0].vector.length;
	balls[0].vector.Y = y / balls[0].vector.length;

	balls[0].speed = balls[0].vector.length / (cycleLength*cyclesSinceLastCameraInput);

	if (balls[1].state != known)
	{
		ball.vector.X = balls[0].vector.X;
		ball.vector.Y = balls[0].vector.Y;

		ball.vector.length = sqrt(
			(balls[0].center.X - balls[1].center.X) * (balls[0].center.X - balls[1].center.X)
			+
			(balls[0].center.Y - balls[1].center.Y) * (balls[0].center.Y - balls[1].center.Y)
			);

		ball.speed = balls[0].speed;
	}
	else if (balls[2].state != known)
	{
		ball.vector.X = (balls[0].vector.X + balls[1].vector.X) / 2;
		ball.vector.Y = (balls[0].vector.Y + balls[1].vector.Y) / 2;

		ball.vector.length = sqrt(
			(balls[0].vector.X*balls[0].vector.length + balls[1].vector.X*balls[1].vector.length)
			*
			(balls[0].vector.X*balls[0].vector.length + balls[1].vector.X*balls[1].vector.length)
			+
			(balls[0].vector.Y*balls[0].vector.length + balls[1].vector.Y*balls[1].vector.length)
			*
			(balls[0].vector.Y*balls[0].vector.length + balls[1].vector.Y*balls[1].vector.length)
			) / 2;


		ball.speed = (balls[0].speed + balls[1].speed) / 2;
	}


		//if (balls[2].state==known)
	else
	{
		ball.vector.X = (balls[0].vector.X + balls[1].vector.X + balls[2].vector.X) / 3;
		ball.vector.Y = (balls[0].vector.Y + balls[1].vector.Y + balls[2].vector.Y) / 3;

		ball.vector.length = sqrt(
			(balls[0].vector.X*balls[0].vector.length + balls[1].vector.X*balls[1].vector.length + balls[2].vector.X*balls[2].vector.length)
			*
			(balls[0].vector.X*balls[0].vector.length + balls[1].vector.X*balls[1].vector.length + balls[2].vector.X*balls[2].vector.length)
			+
			(balls[0].vector.Y*balls[0].vector.length + balls[1].vector.Y*balls[1].vector.length + balls[2].vector.Y*balls[2].vector.length)
			*
			(balls[0].vector.Y*balls[0].vector.length + balls[1].vector.Y*balls[1].vector.length + balls[2].vector.Y*balls[2].vector.length)
			) / 3;


		ball.speed = (balls[0].speed + balls[1].speed + balls[2].speed) / 3;
	}



	ball.vector.X /= sqrt(ball.vector.X*ball.vector.X + ball.vector.Y*ball.vector.Y);
	ball.vector.Y /= sqrt(ball.vector.X*ball.vector.X + ball.vector.Y*ball.vector.Y);

	ball.lastCenter.X = ball.center.X - ball.vector.X*ball.vector.length;
	ball.lastCenter.Y = ball.center.Y - ball.vector.Y*ball.vector.length;

}

void BaseStrategy::CalculateDesiredAxisPositions()
{
	int currentDist;
	int minDist;
	bool foundBest;
	int bestJ;

	// Update axes
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < axes[i].dummies.size(); j++) {
			axes[i].dummies[j].realPos = axes[i].realDisplacement + axes[i].dummies[j].offset;
		}

		for (int j = 0; j < opponentAxes[i].dummies.size(); j++) {
			opponentAxes[i].dummies[j].realPos = opponentAxes[i].realDisplacement + opponentAxes[i].dummies[j].offset;
		}

	}

	// basic defense
	for (int i = 3; i >= 0; i--)	// from forwards to goalkeeper
	{
		foundBest = false;

		//	if (axes[i].intersectionY != 5000)
		{
			minDist = 10000;
			for (int j = 0; j < axes[i].dummies.size(); j++)
			{
				currentDist = axes[i].desiredIntercept - axes[i].dummies[j].realPos;

				if (abs(currentDist) < minDist && axes[i].realDisplacement + currentDist < axes[i].y_max && axes[i].realDisplacement + currentDist > axes[i].y_min)	// check displacement limit
				{
					minDist = abs(currentDist);
					axes[i].desiredDisplacement = axes[i].realDisplacement + currentDist;

					foundBest = true;
					bestJ = j;
				}
			}			

			// novy zpusob
			// kdyz foundBest==false, nenasel jsem kam pozici kam bych mohl jet nejkratsi cestou
			if (foundBest == false)
			{

				if (axes[i].desiredIntercept > 0)  // na horni max
				{
					axes[i].desiredDisplacement = axes[i].y_max;
				}
				else if (axes[i].desiredIntercept < 0)
				{
					axes[i].desiredDisplacement = axes[i].y_min;
				}
				else    //  obranci se nedostanou na Y=0
				{
					axes[i].desiredDisplacement = axes[i].y_min;
				}
			}

		}
	}
}
