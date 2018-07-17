#include <math.h>
#include "Global.h"
#include "ExtraMath.h"


Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

float Vec2::lengthSquared() {
	return x * x + y * y;
}

Vec2 Vec2::normalise() {
	float length = sqrt(this->lengthSquared());

	if (length != 0) {
		return Vec2(this->x / length, this->y / length);
	}
	else return Vec2(0, 0);
}


Vec2 Vec2::scale(float s) {
	return Vec2(x * s, y * s);
}

bool Vec2::equal(Vec2 a) {
	return ((x == a.x) && (y == a.y));
}


bool Vec2::equal(float ax, float ay) {
	return ((x == ax) && (y == ay));
}

/*
Vec2 VecCreate(float Ax, float Ay) {
Vec2 C;
C.x = Ax;
C.y = Ay;
return C;
}*/

Vec2 vecSum(Vec2 A, Vec2 B) {
	Vec2 C;
	C.x = A.x + B.x;
	C.y = A.y + B.y;
	return C;
}

Vec2 vecDiff(Vec2 B, Vec2 A) {
	Vec2 C;
	C.x = B.x - A.x;
	C.y = B.y - A.y;
	return C;
}

Vec2 vecDiff(float Bx, float By, Vec2 A) {
	Vec2 C;
	C.x = Bx - A.x;
	C.y = By - A.y;
	return C;
}

/*
Vec2 vecScale(Vec2 A, float s) {
Vec2 C;
C.x = A.x * s;
C.y = A.y * s;
return C;
}*/

/*
bool vecEqual(Vec2 A, Vec2 B) {
return ((A.x == B.x) && (A.y == B.y));
}
*/

float vecDot(Vec2 A, Vec2 B) {
	return A.x * B.x + A.y * B.y;
}

float clamp(float min, float max, float value) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}


bool inside(float min, float max, float value) {
	if (value > min && value < max) return true;
	return false;
}

float absf(float x) {
	return x >= 0 ? x : -x;
}

float min(float a, float b) {
	return a > b ? b : a;
}
