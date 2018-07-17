#include "StrategyC.h"


StrategyC::StrategyC()
{
	mode = defense;
	okoliH = 200;
	okoliW = 150;
	cameraTolerance = 0.35;

}



StrategyC::~StrategyC()
{
}



void StrategyC::Process()
{
	cyclesSinceLastCameraInput++;

	// pokud neutocim
	if (mode != attack)
	{
		// check if attack is possible
		int AxisWithBall = CheckIfCanAttack();

		switch (AxisWithBall)
		{
		case -4:
		case -3:
		case -2:
		case -1:
			BackwardAttack(-(AxisWithBall + 1));
			break;

		case 1:
		case 2:
		case 3:
		case 4:	// attack
			Attack(AxisWithBall - 1);	// obsahuje obranu zadnimi
			break;

		case 0:	// defense
			Defend();
			break;
		}
	}
	// attack mode bude vypnut ve CameraInput, po moznem odrazu
	else // mode == attack
	{
		cyclesSinceAttackBeginning++;

		Defend();
	}

}



void StrategyC::Defend()
{
	if (mode == attack)
	{
		for (int i = 0; i < 4; i++)
		{
			axes[i].desiredIntercept = ball.center.Y;

			if (ball.center.X > axes[i].X + axes[i].xDisplacement && (axes[i].mode != forwardShoot && axes[i].mode != backwardShoot))
			{
				axes[i].mode = forwardDefense;
			}
		}
	}
	else // mode == defense
	{
		if (ball.state == unknown)
		{
			for (int i = 0; i < 4; i++)	// neznam smer
			{
				axes[i].desiredIntercept = ball.center.Y;

				if (ball.center.X > axes[i].X + axes[i].xDisplacement) // mic pred osou
				{
					axes[i].mode = forwardDefense;
				}
				else
				{
					axes[i].mode = backwardDefense;
				}
			}

		}
		else if (ball.vector.X > 0)// doprava
		{
			for (int i = 0; i < 4; i++)
			{
		//		if (axes[i].intersectionY == -10000) // neprotina
				if (ball.center.X > axes[i].X + axes[i].xDisplacement)
				{

					axes[i].desiredIntercept = ball.center.Y;
					axes[i].mode = forwardDefense;

				}
				else // protina
				{

					axes[i].desiredIntercept = axes[i].intersectionY;
					axes[i].mode = backwardDefense;

				}
			}
		}
		else if (ball.vector.X < 0) //doleva
		{
			for (int i = 0; i < 4; i++)
			{
			//	if (axes[i].intersectionY == -10000) // neprotina
				if (ball.center.X < axes[i].X + axes[i].xDisplacement)
				{

					axes[i].desiredIntercept = ball.center.Y;
					axes[i].mode = backwardDefense;

				}
				else
				{
					axes[i].desiredIntercept = axes[i].intersectionY;
					axes[i].mode = forwardDefense;
				}
			}
		}
	}

	CalculateDesiredAxisPositions();
}

void StrategyC::CalculateDesiredAxisPositions()
{
	int currentDist;
	int minDist;
	bool foundBest;
	int bestJ;

	// basic defense
	for (int i = 3; i >= 0; i--)	// from forwards to goalkeeper
	{
		foundBest = false;

		//	if (axes[i].intersectionY != 5000)
		{
			minDist = 10000;
			for (int j = 0; j < axes[i].dummies.size(); j++)
			{
				axes[i].dummies[j].realPos = axes[i].realDisplacement + axes[i].dummies[j].offset;
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

void StrategyC::Attack(int index)
{
	// osy pred micem brani, s micem strili, pred micem zvednou


	//PyramidDefense(index);

	axes[index].mode = forwardShoot;
	//	axes[index].desiredDisplacement = 0;

	for (int i = index + 1; i < 4; i++)
	{
		axes[i].mode = raised;
		//	axes[i].intersectionY = 0;
	}

	mode = attack;

	cyclesSinceAttackBeginning = 0;
}

void StrategyC::BackwardAttack(int index)
{
	// osy pred micem brani, s micem strili, pred micem zvednou


	//PyramidDefense(index);

	axes[index].mode = backwardShoot;
	//	axes[index].desiredDisplacement = 0;

	for (int i = index + 1; i < 4; i++)
	{
		axes[i].mode = raised;
		//	axes[i].intersectionY = 0;
	}

	mode = attack;

	cyclesSinceAttackBeginning = 0;
}

int StrategyC::CheckIfCanAttack()
{

	// check forward shoot
	for (int i = 0; i < 4; i++)
	{
		//	if (ball.center.X - ball.radius - (axes[i].X+axes[i].xDisplacement) < okoliW && ball.center.X - (axes[i].X +axes[i].xDisplacement)> 0)
		if (ball.center.X - ball.radius - axes[i].X < okoliW && ball.center.X - (axes[i].X + axes[i].xDisplacement) > 0)
		{

			for (int j = 0; j < axes[i].dummies.size(); j++)
			{

				if (abs(axes[i].dummies[j].realPos - ball.center.Y) < okoliH && ball.state==unknown)
					return i + 1;
			}
		}

	}

	// check backward shoot
	for (int i = 0; i < 4; i++)
	{
		//	if ((axes[i].X + axes[i].xDisplacement) - (ball.center.X + ball.radius) < okoliW && (axes[i].X + axes[i].xDisplacement) - ( ball.center.X)  > 0)
		if (axes[i].X - (ball.center.X + ball.radius) < okoliW && (axes[i].X + axes[i].xDisplacement) - (ball.center.X) > 0)

		{

			for (int j = 0; j < axes[i].dummies.size(); j++)
			{

				if (abs(axes[i].dummies[j].realPos - ball.center.Y) < okoliH && ball.state == unknown)
					return -(i + 1);
			}
		}

	}

	return 0;
}


void StrategyC::CameraInput(int x, int y)
{

	balls[2] = balls[1];
	balls[1] = balls[0];
	balls[0].center.X = x;
	balls[0].center.Y = y;

	ball.center = balls[0].center;

	SetBall(x - balls[1].center.X, y - balls[1].center.Y);

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
		if (abs(angle) < cameraTolerance && ball.speed > 3)
		{
			ball.state = known;

			//SetBall(x - balls[1].center.X, y - balls[1].center.Y);

		}

		else // mohl byt odraz
		{
			ball.state = unknown;
			balls[0].state = unknown;
			balls[1].state = unknown;
			balls[2].state = unknown;

			// end attack mode
			if (mode == attack && cyclesSinceAttackBeginning >= cyclesSinceLastCameraInput)
			{
				mode = defense;
			}

			//	ball.vector.X = 0;
			//	ball.vector.Y = 0;
		}
	}
	else // unknown or initial
	{
		if (ball.state == unknown && ball.speed > 3)
		{
			ball.state = known;
			balls[0].state = known;
			//	SetBall(x - balls[1].center.X, y - balls[1].center.Y);

		}
		else // initial
		{
			ball.state = unknown;
			balls[0].state = unknown;
		}

	}
	if (ball.speed<3 && abs(ball.vector.Y) > 0.9)
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
void StrategyC::SetBall(double x, double y)
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

// unused
void StrategyC::PyramidDefense(int index)
{
	int pyrLayer = 0;
	int minDist;
	int currentDist;

	for (int i = index - 1; i >= 0; i--)	// from forwards to goalkeeper
	{
		if (axes[i].X < ball.center.X)
		{
			switch (pyrLayer)
			{
			case 0:

				break;
			case 1:
				axes[i].intersectionY += DummyY;
				break;
			case 2:
				axes[i].intersectionY -= DummyY;
				break;
			case 3:
				axes[i].intersectionY += 2 * DummyY;
				break;
			default:
				break;
			}
			pyrLayer++;
		}
		if (axes[i].intersectionY != 5000)
		{
			minDist = 10000;
			for (int j = 0; j < axes[i].dummies.size(); j++)
			{
				axes[i].dummies[j].realPos = axes[i].realDisplacement + axes[i].dummies[j].offset;
				currentDist = axes[i].intersectionY - axes[i].dummies[j].realPos;

				if (abs(currentDist) < minDist && axes[i].realDisplacement + currentDist < axes[i].y_max && axes[i].realDisplacement + currentDist > axes[i].y_min)	// check displacement limit
				{
					minDist = abs(currentDist);
					axes[i].desiredDisplacement = axes[i].realDisplacement + currentDist;
				}
			}
		}
	}
}

