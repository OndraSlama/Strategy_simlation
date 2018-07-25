#pragma once
#include "BaseStrategy.h"


class StrategyB : public BaseStrategy
{
	public:
	StrategyB();
	~StrategyB();

	// Inherited from BaseStrategy
	void Process();
	void Defend();
	void PyramidDefense();
	void Kick(int i);
	void BackwardKick(int i);
	int CheckIfCanAttack();	
	int CheckIfOponentHasBall();

	int okoliW;
	int okoliH;
	int shotSpeedLimit;
	int maxCyclesAfterAttack;

};
