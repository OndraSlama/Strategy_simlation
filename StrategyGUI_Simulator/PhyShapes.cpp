#include <math.h>

#include "Global.h"
#include "ExtraMath.h"
#include "PhyShapes.h"


Phy::Circle::Circle(float r) {
	this->radius = r;
}

void Phy::Circle::move() {

	/*      simulating friction        \\
	\
	acc                      \
	| ______ (ballacc)  \
	slope |/|                      \
	-----+-/-+----> velocity        \
	_____|/|        +=limit         \
	(-ballfriciton)|                        */

	//due to step solving we need to introduce a slope
	//to the function of acceleration so that velocity can
	//ever reach 0

	float limit = 10;
	float slope = ballacc / limit;
	float velocity_squared = velocity.lengthSquared();
	float acc;

	if (velocity_squared > limit * limit) {
		acc = ballacc;
	}
	else {
		acc = sqrt(velocity_squared) * slope;
	}

	acceleration = velocity.normalise().scale(acc * -1);

	if (acceleration.lengthSquared() < 1) acceleration = Vec2(0, 0);

	if (position.y > boardheight / 2 - slopesize) {
		slope_acceleration.y = -slopeacc;
	}
	else if (position.y < -boardheight / 2 + slopesize) {
		slope_acceleration.y = slopeacc;
	}
	else {
		slope_acceleration.y = 0;
	}


	velocity.x += (acceleration.x + slope_acceleration.x) * TIMESTEP;
	velocity.y += (acceleration.y + slope_acceleration.y) * TIMESTEP;

	if (velocity.lengthSquared() < 1) velocity = Vec2(0, 0);

	position.x += velocity.x * TIMESTEP;
	position.y += velocity.y * TIMESTEP;
}


void Phy::Axis::move() {

	position.y += velocity.y * TIMESTEP*100;
	angle += angular_velocity * TIMESTEP;

	if (angle > 900) {
		angle = 900;
		angular_velocity = 0;
	}
	else if (angle < -900) {
		angle = -900;
		angular_velocity = 0;
	}

	if (!inside(-450, 450, angle)) {
		collide = false;
	}
	else collide = true;


	float angle_rad = angle * 3.1415 / 1800;

	x_offset = playerheight * sin(angle_rad);
	velocity.x = playerheight * (angular_velocity * 3.1415 / 1800) * cos(angle_rad);


	if (position.y < y_min) {
		position.y = y_min;
		velocity.y = 0;
	}
	else if (position.y > y_max) {
		position.y = y_max;
		velocity.y = 0;
	}
}

void Phy::Axis::movePos(float pos) {
	float last_y = position.y;
	//float last_ang = angle;

	position.y = pos;
	velocity.y = (position.y - last_y) / TIMESTEP;

	if (position.y < y_min) {
		position.y = y_min;
		velocity.y = 0;
	}
	else if (position.y > y_max) {
		position.y = y_max;
		velocity.y = 0;
	}
}

void Phy::Axis::moveAng(float ang) {
	float last_ang = angle;

	if (angle > 900) {
		angle = 900;
	}
	else if (angle < -900) {
		angle = -900;
	}

	if (!inside(-450, 450, angle)) {
		collide = false;
	}
	else collide = true;

	angle = ang;
	angular_velocity = (angle - last_ang) / TIMESTEP;

	x_offset = playerheight * sin(angle * 3.1415 / 1800);
	velocity.y = playerheight * (angular_velocity * 3.1415 / 1800) * cos(angle * 3.1415 / 1800);


}

Vec2 Phy::Axis::getPosition() {
	return vecSum(position, Vec2(x_offset, 0));
}


Vec2 Phy::calculateNormal(Circle* circle, Box* box, Vec2* close) {
	//Calculates normal from closest point of box to centre of ball
	//@ Vec2* close only for debug

	Vec2 closest = box->position;

	float xmax = (box->position.x + box->width / 2);
	float xmin = (box->position.x - box->width / 2);

	float ymax = (box->position.y + box->height / 2);
	float ymin = (box->position.y - box->height / 2);

	closest = Vec2(clamp(xmin, xmax, circle->position.x), clamp(ymin, ymax, circle->position.y));

	Vec2 normal;

	if (closest.equal(circle->position)) {
		//ball centre is inside box
		//std::cout << "AJAJAJ\n";
		Vec2 boxcentre_offset = vecDiff(closest, box->position);

		if (absf(boxcentre_offset.x) > absf(boxcentre_offset.y)) {
			//clamp to left or right
			if (boxcentre_offset.x > 0) {
				closest.x = xmax;
			}
			else {
				closest.x = xmin;
			}
		}
		else {
			//clamp to top or bottom
			if (boxcentre_offset.y > 0) {
				closest.y = ymax;
			}
			else {
				closest.y = ymin;
			}
		}

		normal = vecDiff(closest, circle->position);

	}
	else {
		//ball centre is outside box
		normal = vecDiff(circle->position, closest);
	}

	*close = closest;

	return normal;

}

bool Phy::AABBvsCircle(Contact *c) {
	Circle* circle = c->circle;
	Box* box = &c->axis.player[c->player];
	box->position = Vec2(c->axis.position.x + c->axis.x_offset, c->axis.position.y + c->axis.player[c->player].y_offset);

	bool collide = false;

	//Closest point on Box to the center of Circle - only for debug
	Vec2 closest;


	Vec2 normal = calculateNormal(circle, box, &closest);


	if (normal.lengthSquared() < circle->radius * circle->radius) {
		collide = true;
		//std::cout << "contact" << "\t" << 
		c->penetration = circle->radius - sqrt(normal.lengthSquared());
		//<< "\n";
		c->normal = normal;


	}


	return collide;
}

bool Phy::boundaryVsCircle(ContactBoundary *c) {
	Circle* circle = c->circle;
	Box* box = c->box;

	bool collide = false;

	//Closest point on Box to the center of Circle
	Vec2 closest;

	Vec2 normal = calculateNormal(circle, box, &closest);


	if (normal.lengthSquared() < circle->radius * circle->radius) {
		collide = true;
		//std::cout << "contact" << "\t" << 
		//std::cout << "BOOOMM\n";
		c->penetration = circle->radius - sqrt(normal.lengthSquared());
		//<< "\n";
		c->normal = normal;

	}

	return collide;
}

void Phy::resolveCollision(Contact* c) {
	Circle* circle = c->circle;
	Box* box = &c->axis.player[c->player];
	box->position = Vec2(c->axis.position.x + c->axis.x_offset, c->axis.position.y + c->axis.player[c->player].y_offset);

	if (!c->axis.collide) return;

	Vec2 direction;

	if (circle->velocity.equal(0, 0)) {
		direction = c->normal.normalise().scale(-1);
	}
	else {
		direction = circle->velocity.normalise();
	}

	if (vecDot(direction, c->normal) > 0) direction = direction.scale(-1); // return;

																		   //std::cout << "OKK\n";

	Vec2 temp; //unused variable, delete from calculateNormal after debugging



	while (absf(c->penetration) > 1) {
		if (!direction.equal(0, 0)) {
			Vec2 error = direction.scale(c->penetration * -1);
			circle->position = vecSum(circle->position, error);
		}

		c->normal = calculateNormal(circle, box, &temp);
		c->penetration = circle->radius - sqrt(c->normal.lengthSquared());
	}

	c->normal = c->normal.normalise();

	Vec2 velAlongNormal = c->normal.scale(vecDot(c->normal, c->axis.velocity));


	//std::cout << c->axis.velocity.x << " " << c->axis.velocity.y << " " << sqrt(c->axis.velocity.lengthSquared()) << " DING\n";
	//std::cout << circle->velocity.x << " " << circle->velocity.y << " " << sqrt(circle->velocity.lengthSquared()) << "BANG\n";

	//std::cout << velAlongNormal.x << " " << velAlongNormal.y << "DOOM\n";

	circle->velocity = vecSum(c->normal.scale(vecDot(c->normal, circle->velocity) * -2), circle->velocity).scale(bounce_ratio);

	circle->velocity = vecSum(circle->velocity, velAlongNormal);

	if (c->normal.y == 0) {
		if (absf(c->axis.angular_velocity) < 10) {
			circle->velocity = circle->velocity.scale((450 + c->axis.angle)*(450 - c->axis.angle) / 202500);
		}
		else {
		//	circle->velocity.y /= 1;
		}
	}

	//std::cout << c->normal.x << " " << c->normal.y << " " << sqrt(c->normal.lengthSquared()) << "BOOM\n";

	//std::cout << circle->velocity.x << " " << circle->velocity.y << " " << sqrt(circle->velocity.lengthSquared()) << "BOING\n";


}

void Phy::resolveCollisionBoundary(ContactBoundary* c) {
	Circle* circle = c->circle;
	Box* box = c->box;

	Vec2 direction;


	if (circle->velocity.equal(0, 0)) {
		direction = c->normal.normalise().scale(-1);
	}
	else {
		direction = circle->velocity.normalise();
	}

	Vec2 temp;

	while (absf(c->penetration) > 1) {
		if (!direction.equal(0, 0)) {
			Vec2 error = direction.scale(c->penetration * -1);
			circle->position = vecSum(circle->position, error);
		}
		c->normal = calculateNormal(circle, box, &temp);
		c->penetration = circle->radius - sqrt(c->normal.lengthSquared());
	}


	c->normal = c->normal.normalise();

	circle->velocity = vecSum(c->normal.scale(vecDot(c->normal, circle->velocity) * -2), circle->velocity);
}

