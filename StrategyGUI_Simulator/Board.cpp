
#include "Global.h"
#include "ExtraMath.h"
#include "PhyShapes.h"

#include "Board.h"


/*
Phy::Box* boundary;
Phy::Contact* contact = new Phy::Contact;
Phy::ContactBoundary* contactboundary = new Phy::ContactBoundary;
*/
Sim::Sim() {
	contact = new Phy::Contact;
	contactboundary = new Phy::ContactBoundary;

	ball = new Phy::Circle(ballradius);

	boundary = new Phy::Box[6];

	red = new Phy::Axis[4];
	red[0].size = 1;
	red[0].player = new Phy::Box[1];

	red[1].size = 2;
	red[1].player = new Phy::Box[2];


	red[2].size = 5;
	red[2].player = new Phy::Box[5];


	red[3].size = 3;
	red[3].player = new Phy::Box[4];

	blu = new Phy::Axis[4];
	blu[0].size = 1;
	blu[0].player = new Phy::Box[1];

	blu[1].size = 2;
	blu[1].player = new Phy::Box[2];


	blu[2].size = 5;
	blu[2].player = new Phy::Box[5];

	blu[3].size = 3;
	blu[3].player = new Phy::Box[4];
}

void Sim::setup() {

	ball->position = Vec2(default_ballx, default_bally);
	ball->velocity = Vec2(0, 0);
	ball->acceleration = Vec2(0, 0);
	ball->slope_acceleration = Vec2(0, 0);

	//boundary\\
		[0] left top\
	[1] left bottom\
	[2] right top\
	[3] right bottom \
	[4] top\
	[5] bottom\


	boundary[0].position = Vec2(-200, boardheight / 4 + goalsize / 4);
	boundary[0].y_offset = 0;
	boundary[0].height = (boardheight - goalsize) / 2;
	boundary[0].width = 400;

	boundary[1] = boundary[0];
	boundary[1].position.y = -boundary[0].position.y;

	boundary[2] = boundary[0];
	boundary[2].position.x = boardwidth + 200;

	boundary[3] = boundary[1];
	boundary[3].position.x = boardwidth + 200;


	boundary[4].position = Vec2(boardwidth / 2, -boardheight / 2 - 200);
	boundary[4].y_offset = 0;
	boundary[4].height = 400;
	boundary[4].width = boardwidth;

	boundary[5] = boundary[4];
	boundary[5].position.y = boardheight / 2 + 200;



	//RED

	red[0].position = Vec2(800, 0);
	red[1].position = Vec2(2300, 0);
	red[2].position = Vec2(5300, 0);
	red[3].position = Vec2(8300, 0);


	red[0].player[0].y_offset = 0;
	//red[0].player[0].min = Vec2(0, 0);
	//red[0].player[0].max = Vec2(boxwidth, boxheight);



	red[1].player[0].y_offset = 1190;
	red[1].player[1].y_offset = -1190;

	red[2].player[0].y_offset = 2380;
	red[2].player[1].y_offset = 1190;
	red[2].player[2].y_offset = 0;
	red[2].player[3].y_offset = -1190;
	red[2].player[4].y_offset = -2380;

	red[3].player[0].y_offset = 2080;
	red[3].player[1].y_offset = 0;
	red[3].player[2].y_offset = -2080;

	//BLU

	blu[0].position = Vec2(boardwidth - 800, 0);
	blu[1].position = Vec2(boardwidth - 2300, 0);
	blu[2].position = Vec2(boardwidth - 5300, 0);
	blu[3].position = Vec2(boardwidth - 8300, 0);


	blu[0].player[0].y_offset = 0;

	blu[1].player[0].y_offset = 1190;
	blu[1].player[1].y_offset = -1190;

	blu[2].player[0].y_offset = 2380;
	blu[2].player[1].y_offset = 1190;
	blu[2].player[2].y_offset = 0;
	blu[2].player[3].y_offset = -1190;
	blu[2].player[4].y_offset = -2380;


	blu[3].player[0].y_offset = 2080;
	blu[3].player[1].y_offset = 0;
	blu[3].player[2].y_offset = -2080;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < red[i].size; j++) {
			red[i].player[j].height = boxheight;
			red[i].player[j].width = boxwidth;

			blu[i].player[j].height = boxheight;
			blu[i].player[j].width = boxwidth;

			red[i].velocity = (blu[i].velocity = Vec2(0, 0));
			red[i].angle = (blu[i].angle = 0.f);
			red[i].angular_velocity = (blu[i].angular_velocity = 0.f);
			red[i].x_offset = (blu[i].x_offset = 0.f);
			red[i].collide = (blu[i].collide = 1);
		}
	}

	red[0].y_max = (blu[0].y_max = 805);
	red[1].y_max = (blu[1].y_max = 1070);
	red[2].y_max = (blu[2].y_max = 560);
	red[3].y_max = (blu[3].y_max = 870);

	red[0].y_min = (blu[0].y_min = -920);
	red[1].y_min = (blu[1].y_min = -970);
	red[2].y_min = (blu[2].y_min = -540);
	red[3].y_min = (blu[3].y_min = -800);
}

void Sim::moveAxis() {
	for (int i = 0; i < 4; i++) {
		red[i].move();
		blu[i].move();
	}
}

void Sim::move() {
	ball->move();
	moveAxis();
}

void Sim::collide() {

	contact->circle = ball;

	for (int i = 0; i < 4; i++) {

		if (inside(red[i].position.x - 1000, red[i].position.x + 1000, ball->position.x)) {
			for (int j = 0; j < red[i].size; j++) {

				contact->axis = red[i];
				contact->player = j;

				if (AABBvsCircle(contact)) resolveCollision(contact);
			}
		}



		if (inside(blu[i].position.x - 1000, blu[i].position.x + 1000, ball->position.x)) {
			for (int j = 0; j < blu[i].size; j++) {

				contact->axis = blu[i];
				contact->player = j;

				if (AABBvsCircle(contact)) resolveCollision(contact);
			}
		}

	}

	contactboundary->circle = ball;
	for (int i = 0; i < 6; i++) {
		contactboundary->box = &boundary[i];

		if (boundaryVsCircle(contactboundary)) resolveCollisionBoundary(contactboundary);
	}

}


void Sim::del() {
	delete contact;
	delete contactboundary;
	delete ball;
	delete red;
	delete blu;
}