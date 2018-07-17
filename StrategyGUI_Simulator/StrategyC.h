#pragma once
#include "BaseStrategy.h"


class StrategyC : public BaseStrategy
{
public:
	StrategyC();
	~StrategyC();

	// Inherited from BaseStrategy
	void Process();
	void CameraInput(int x, int y);



private:

	void CalculateDesiredAxisPositions();
	void Defend();
	void PyramidDefense(int index = 4);

	void Attack(int i);
	void BackwardAttack(int i);

	int CheckIfCanAttack();
	void SetBall(double, double);
	
	int okoliW;
	int okoliH;

	double cameraTolerance;

};
