#include "StrategyB.h"


StrategyB::StrategyB()
{
	mode = defense;
	okoliH = 200;
	okoliW = 150;
	shotSpeedLimit = 20;
	maxCyclesAfterAttack = 500;	
}

StrategyB::~StrategyB()
{
}

void StrategyB::Process()
{
	cyclesSinceLastCameraInput++;

/*	for (int i = 0; i < 4; i++){
		axes[i].desiredDisplacement = opponentAxes[i].realDisplacement;
	}*/
	
	// pokud neutocim
	if (mode != attack)
	{
		// check if attack is possible
		int AxisWithBall = CheckIfCanAttack();
		
		if(AxisWithBall < 0){
			BackwardKick(-(AxisWithBall + 1));
		}else if(AxisWithBall > 0){
			Kick(AxisWithBall - 1);
		}else{
			Defend();
		}
		
	}
	
	else // mode == attack
	{		
		cyclesSinceAttackBeginning++;
		Defend();
		
		if (ball.state == unknown && cyclesSinceAttackBeginning >= cyclesSinceLastCameraInput)
		{
			mode = defense;
		}
	}
		
	
}

void StrategyB::Defend()
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
				else if (cyclesSinceAttackBeginning > maxCyclesAfterAttack) // míè urèitì prošel za hráèe
				{
					axes[i].mode = backwardDefense;
				}
			}

		}
		else if (ball.vector.X > 0) // do brány oponenta
		{
			
			for (int i = 0; i < 4; i++)
			{
				if (axes[i].intersectionY == -10000) // neprotina
				{

					axes[i].desiredIntercept = ball.center.Y;
					if (cyclesSinceAttackBeginning > maxCyclesAfterAttack || ball.center.X > axes[i].X + axes[i].xDisplacement){ // míè urèitì prošel za hráèe
						axes[i].mode = forwardDefense;
					}

				}
				else // protina
				{

					axes[i].desiredIntercept = axes[i].intersectionY;
					axes[i].mode = backwardDefense;

				}
			}
		}
		else if (ball.vector.X < 0) // do brány robota
		{
			//PyramidDefense();
			for (int i = 0; i < 4; i++)
			{
				if (axes[i].intersectionY == -10000) // neprotina
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


void StrategyB::Kick(int index)
{
	// osy pred micem brani, s micem strili, pred micem zvednou


	axes[index].mode = forwardShoot;

	for (int i = index + 1; i < 4; i++)
	{
		axes[i].mode = raised;
	}

	mode = attack;

	cyclesSinceAttackBeginning = 0;
}

void StrategyB::BackwardKick(int index)
{
	// osy pred micem brani, s micem strili, pred micem zvednou

	axes[index].mode = backwardShoot;

	for (int i = index + 1; i < 4; i++)
	{
		axes[i].mode = raised;
	}

	mode = attack;

	cyclesSinceAttackBeginning = 0;
}

int StrategyB::CheckIfCanAttack()
{

	// check forward shoot
	for (int i = 0; i < 4; i++)
	{
		if ((ball.speed * ball.vector.Y) < shotSpeedLimit){
			if (ball.center.X - ball.radius - axes[i].X < okoliW && ball.center.X - (axes[i].X) > 0)
			{

				for (int j = 0; j < axes[i].dummies.size(); j++)
				{

				if (abs(axes[i].dummies[j].realPos - ball.center.Y) < okoliH)
					return i + 1;
				}
			}
		}

	}

	// check backward shoot
		for (int i = 0; i < 4; i++)
		{
			if ((ball.speed * ball.vector.Y) < shotSpeedLimit){
				if (axes[i].X - (ball.center.X + ball.radius) < okoliW && (axes[i].X + axes[i].xDisplacement) - (ball.center.X) > 0 && axes[i].mode != forwardShoot && axes[i].mode != backwardShoot)

				{

					for (int j = 0; j < axes[i].dummies.size(); j++)
					{

						if (abs(axes[i].dummies[j].realPos - ball.center.Y) < okoliH)
							return -(i + 1);
					}
				}

			}
		}

	return 0;
}

int StrategyB::CheckIfOponentHasBall(){	
	for (int i = 0; i < 4; i++){
		if(ball.center.X < opponentAxes[i].X - okoliW) continue;
		if(ball.center.X > opponentAxes[i].X + okoliW) continue;
		return i;
	}
	return -1;	
}

void StrategyB::PyramidDefense()
{
	int pyrLayer = 0;

	for (int i = 3; i >= 0; i--)	// from forwards to goalkeeper
	{
		if (axes[i].X < ball.center.X && axes[i].intersectionY != -10000)
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
		
	}
}

