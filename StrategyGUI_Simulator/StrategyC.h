#pragma once
#include "BaseStrategy.h"


class StrategyC : public BaseStrategy
{
public:
	StrategyC();
	~StrategyC();

	// Inherited from BaseStrategy
	void Process();

private:

	int Sign(double arg);

	void Defend();
	void Attack();
	void Block();
	void GoalKeeper();
	void Forward();
	
	void PyramidDefence();

	void NormalDefence(int i);
	void RaisedAttack(int i);
	void Kick(int i);
	void BackwardKick(int i);
	void BlockOpponent(int i);
	void GetBehindBall(int i);

	int kickAreaLength;
	int kickAreaWidth;
	int kickAreaStart;
	int kickYSpeedLimit;
	int kickXSpeedLimit;
};
