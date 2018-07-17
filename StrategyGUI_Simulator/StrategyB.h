#pragma once
#include "BaseStrategy.h"


class StrategyB : public BaseStrategy
{
public:
	StrategyB();
	~StrategyB();

	// Inherited from BaseStrategy
	void Process();


	void CalculateDesiredAxisPositions();

	void Defend();
	void PyramidDefense(int index = 4);

	void Attack(int i);
	void BackwardAttack(int i);

	int CheckIfCanAttack();
	void SetBall(double, double);

	

	void CameraInput(int x, int y);

	int okoliW;
	int okoliH;

	double cameraTolerance;


};
