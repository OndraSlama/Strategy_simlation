#ifndef EXTRAMATH_H_
#define EXTRAMATH_H_

struct Vec2 {
	float x;
	float y;

	Vec2() {}
	Vec2(float x, float y);
	Vec2 normalise();
	float lengthSquared();
	Vec2 scale(float s);
	bool equal(Vec2 a);
	bool equal(float ax, float ay);
};


Vec2 vecSum(Vec2 A, Vec2 B);

Vec2 vecDiff(Vec2 B, Vec2 A);

Vec2 vecDiff(float Bx, float By, Vec2 A);

float vecDot(Vec2 A, Vec2 B);

float clamp(float min, float max, float value);

bool inside(float min, float max, float value);

float min(float a, float b);

float absf(float x);

#endif // !EXTRAMATH_H_