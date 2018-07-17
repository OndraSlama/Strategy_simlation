#pragma once
#include "Structs.h"
#include "Ball.h"
#include <vector>
#include <math.h>


class BaseStrategy
{
public:
	BaseStrategy();
	~BaseStrategy();

	virtual void Process() = 0;
	virtual void CameraInput(int, int) = 0;

	void Reset();
	virtual void CalculateTrajectory();
	virtual void CalculateAxesIntersections();

	Axis axes[4]; // dummies positions
	Axis opponentAxes[4]; 

	StrategyMode mode;
	Ball ball; // zfiltrovany mic, se kterym pocitam
	vector<Line> trajectory;

protected:

	void SetupAxis();

	virtual Line TrajectoryUntilBounce(Ball&, bool&);


	Ball balls[3]; // skutecne pozice micu

	int DummyX;
	int DummyY;
	Line field[4]; // field edges lines
	int minSpeedLimit;

	int cyclesSinceAttackBeginning; // nepujdu na unknown mode hned po utoku, kvuli odrazu
	int cycleLength;
	int cyclesSinceLastCameraInput;
	int goalWidth;
};