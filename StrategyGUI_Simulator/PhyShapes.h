#ifndef PHYSHAPES_H_
#define PHYSHAPES_H_

namespace Phy {

	struct Box {
		float height;
		float width;

		float y_offset; //offset from zero on axis
		Vec2 position;
	};

	struct Circle {
		Circle(float r);

		float radius;

		Vec2 position;
		Vec2 velocity;
		Vec2 acceleration;
		Vec2 slope_acceleration;

		void move(); //move ball according to velocity and acceleration

	};


	struct Axis {
		Box* player; //array of players
		int size; //number of players on axis

		Vec2 velocity;
		Vec2 position;

		float angle;
		float angular_velocity;

		bool collide; //1 if within collision angle

		float y_max; //max and min y position of axis
		float y_min;

		float x_offset; //used when axis is at angle

		void move(); //move axis according to set velocity
		void movePos(float pos); //move axis to new position while computing velocity 
		void moveAng(float ang);
		Vec2 getPosition(); //gets actual position including x_offset
	};


	struct Contact {
		Circle* circle;
		Axis axis;
		int player;

		Vec2 normal;
		float penetration;
	};

	struct ContactBoundary {
		Circle* circle;
		Box* box;

		Vec2 normal;
		float penetration;
	};

	Vec2 calculateNormal(Circle* circle, Box* box, Vec2* close);

	bool AABBvsCircle(Contact *c);

	bool boundaryVsCircle(ContactBoundary *c);

	void resolveCollision(Contact* c);

	void resolveCollisionBoundary(ContactBoundary* c);

}
#endif // !PHYSHAPES_H_