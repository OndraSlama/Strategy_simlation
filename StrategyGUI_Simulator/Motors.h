#pragma once
#include "Structs.h"
#include <vector>
public class Motors
{
public:
	//Axis* axes;
	Axis* axes[4];
	//vector<Axis>* axes2;
	int maxAcc = 3;
	Motors();

	void moveAxis();
};

