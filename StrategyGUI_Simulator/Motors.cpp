#include "Motors.h"



Motors::Motors()
{
}

void Motors::moveAxis()
{

	for (auto &axis : axes)
	{
		
		if (axis->desiredDisplacement > axis->realDisplacement)
		{
			if (axis->speed >= 0) // chci nahoru, jedu nahoru
			{
			axis->speed += maxAcc;
			}
			else  // else stop
			{
				axis->speed = 0;
			}

		}
		else if (axis->desiredDisplacement < axis->realDisplacement)
		{
			if (axis->speed <= 0) // chci dolu, jedu dolu
			{
				axis->speed -= maxAcc;
			}
			else  // else stop
			{
				axis->speed = 0;
			}
		}

		// reached desired position
		if (abs(axis->realDisplacement - axis->desiredDisplacement) < abs(axis->speed))
		{
			axis->realDisplacement = axis->desiredDisplacement;
			axis->speed = 0;
		}
		else
		{
			axis->realDisplacement += axis->speed;
		}
	}
	//*/
}

