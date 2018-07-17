#ifndef BOARD_H_
#define BOARD_H_

#include "PhyShapes.h"

/*
extern Phy::Circle* ball;
extern Phy::Box* boundary;
extern Phy::Axis* blu;
extern Phy::Axis* red;
*/

struct Sim {
public:
	Sim();

	

	void setup();
	void move();
	void moveAxis();
	void collide();
	void del();

	Phy::Circle* ball;
	Phy::Axis* blu;
	Phy::Axis* red;

	Phy::Box* boundary; //Private if SFML not needed

private:

	Phy::Contact* contact;
	Phy::ContactBoundary* contactboundary;
};


/*
void setupSimulation();
void moveSimulation();
void collideSimulation();
void deleteSimulation();
*/

#endif