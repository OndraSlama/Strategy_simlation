#include "StrategyC.h"

StrategyC::StrategyC()
{
	mode = defense;
	cameraTolerance = 0.53;
	kickAreaLength = 300;
	kickAreaWidth = 200;
	kickAreaStart = 200;
	kickYSpeedLimit = 10;
	kickXSpeedLimit = 40;
}

StrategyC::~StrategyC()
{
}

void StrategyC::Process()
{
	cyclesSinceLastCameraInput++;

	if (ball.state == known) {
		if (ball.vector.X > 0) {	// ball is heading to opponent goal
			mode = attack;
		}
		else{						// ball is heading to own goal
			mode = defense;
		}
	}

	Defend(); // Performs defending action
	Attack(); // Performs attack
	Block(); // Block if infront of opponent with ball
	GoalKeeper(); // Special behaviour for goal keeper
	Forward(); // Special behaviour for 
	
	CalculateDesiredAxisPositions(); // Calculate where the axis should move based on desired positions of dummies	
}

void StrategyC::Defend() {

	if (mode == defense && ball.state == known) {
		PyramidDefence();
	}
	else {
		for (int i = 0; i < 4; i++)	{
			NormalDefence(i);
		}
	}
}

void StrategyC::Attack() {

	for (int i = 0; i < 4; i++) {
		if (ball.vector.X > 0 && ball.center.X < axes[i].X){
			RaisedAttack(i);
		}else if (ball.state == unknown && ball.center.X - ball.radius < axes[i].X) {
			RaisedAttack(i);
		}

		Kick(i);
	}
}

void StrategyC::Block(){

	if (ball.state == unknown) {
		for (int i = 1; i < 4; i++)	{		
			BlockOpponent(i);
		}
	}
}

void StrategyC::GoalKeeper() {
	if (ball.center.X < axes[0].X) {
		GetBehindBall(0);
	}
	Kick(0);	
}

void StrategyC::Forward() {
	if (ball.center.X > axes[3].X) {

		if (ball.speed > kickXSpeedLimit) 
			return;

		// check if in area of kick
		if (ball.center.X > axes[3].X + 2*kickAreaLength)	
			return;

		if (ball.center.X < axes[3].X + (axes[3].xDisplacement < -kickAreaStart ? -kickAreaStart : axes[3].xDisplacement)) 
			return;

		// check for individual dummy
		for (int j = 0; j < axes[3].dummies.size(); j++) {

			if (abs(axes[3].dummies[j].realPos - ball.center.Y) < 1.5 * kickAreaWidth) {
				axes[3].mode = forwardShoot;
				mode = attack;
				break;
			}
		}
	}
}

void StrategyC::PyramidDefence() {

	int pyrLayer = 0;

	for (int i = 3; i >= 0; i--)	// from forwards to goalkeeper
	{
		int y = axes[i].intersectionY;
		int sign = Sign(y);

		axes[i].desiredIntercept = ball.center.Y;

		if (ball.center.X > axes[i].X && y != -10000) // If ball is in front of axis and the direction is overlapping with the axis
		{
			switch (pyrLayer)
			{
			case 0:
				axes[i].desiredIntercept = y;
				break;
			case 1:
				axes[i].desiredIntercept = y - sign * DummyY;
				break;
			case 2:
				axes[i].desiredIntercept = y + sign * DummyY;
				break;
			case 3:
				axes[i].desiredIntercept = y - 2 * sign *DummyY;
				break;
			default:
				break;
			}
			pyrLayer++;
			axes[i].mode = forwardDefense;
		}
	}
}

void StrategyC::NormalDefence(int i) {

	axes[i].desiredIntercept = ball.center.Y;

	if (ball.center.X > axes[i].X + (axes[i].xDisplacement < -kickAreaStart ? -kickAreaStart : axes[i].xDisplacement)) {
		axes[i].mode = forwardDefense;
	}
	else {
		axes[i].mode = backwardDefense;
	}

	if (ball.state == unknown) {
		axes[i].mode = straight;
	}
}

void StrategyC::RaisedAttack(int i) {	

	axes[i].mode = raised;

	int y;
	int sign = Sign(ball.vector.Y);

	if (ball.state == known && mode == attack) {
		y = axes[i].intersectionY;
	}
	else {
		y = ball.center.Y;
	}

	// to avoid blocking view of the ball
	axes[i].desiredIntercept = y + 2 * sign * ball.radius;

	if (ball.center.X > axes[i].X + (axes[i].xDisplacement < -2*kickAreaStart ? -2*kickAreaStart : axes[i].xDisplacement)) {
		axes[i].desiredIntercept = ball.center.Y;
	}
}

void StrategyC::Kick(int i){
	
	// check speed limits
	if (abs(ball.speed * ball.vector.Y) > kickYSpeedLimit || abs(ball.speed * ball.vector.X) > kickXSpeedLimit) {
		return;
	}

	// check if in area of kick
	if (ball.center.X > axes[i].X + kickAreaLength) {
		return;
	}

	if (ball.center.X < axes[i].X + (axes[i].xDisplacement < -kickAreaStart ? -kickAreaStart : axes[i].xDisplacement)) {
		return;
	}		

	// check for individual dummy
	for (int j = 0; j < axes[i].dummies.size(); j++) {

		if (abs(axes[i].dummies[j].realPos - ball.center.Y) < kickAreaWidth){
			axes[i].mode = forwardShoot;
			mode = attack;
			break;
		}
	}	
}

void StrategyC::BlockOpponent(int i) {
	
	if (abs(ball.center.X - opponentAxes[i].X) > kickAreaLength) {
		return;
	}

	// check for individual dummy
	int gap = abs(opponentAxes[i].dummies[0].realPos - opponentAxes[i].dummies[1].realPos);

	for (int j = 0; j < opponentAxes[i].dummies.size(); j++) {
		if (abs(opponentAxes[i].dummies[j].realPos - ball.center.Y) <= gap/2) {
			axes[4 - i].desiredIntercept = opponentAxes[i].dummies[j].realPos;
			axes[4 - i].mode = forwardDefense;
			break;
		}
	}
}

void StrategyC::GetBehindBall(int i) {
	axes[i].mode = exactAngle;

	if (ball.center.X < axes[i].X + axes[i].xDisplacement) {

		axes[i].desiredIntercept = ball.center.Y - 3 * Sign(ball.center.Y) * ball.radius;
		axes[i].mode = straight;

		if (abs(axes[i].dummies[0].realPos - ball.center.Y) > 2 * ball.radius) {
			axes[i].mode = exactAngle;
			axes[i].desiredAngle < -450 ? axes[i].desiredAngle = -450 : axes[i].desiredAngle -= 50;
		}
	}

	if (ball.center.X > axes[i].X + axes[i].xDisplacement) {
		axes[i].desiredIntercept = ball.center.Y;
	}

	if (ball.center.X > axes[i].X) {
		axes[i].desiredAngle = 0;
	}
}

void StrategyC::BackwardKick(int i) {

	/*axes[index].mode = backwardShoot;

	for (int i = index + 1; i < 4; i++)	{
		axes[i].mode = raised;
	}*/
}

int StrategyC::Sign(double arg) {
	if (arg > 0) return 1;
	if (arg < 0) return -1;
	return 0;
}
