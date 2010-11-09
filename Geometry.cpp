#include "Geometry.h"


void Triangle2Di::computeBarycentricConstants() {
	f_231 = auxBarycentricFunction(v2, v3, v1);
	f_312 = auxBarycentricFunction(v3, v1, v2);
	f_123 = auxBarycentricFunction(v1, v2, v3);
}



Vector3f Triangle2Di::getBarycentricCoordinates(Vector2i p){
	float _alpha, _beta, _gamma;

	if ((f_231 == 0.0f) && (f_312 == 0.0f) && (f_123 == 0.0f)) {
		computeBarycentricConstants();
	}

	_alpha = auxBarycentricFunction(v2, v3, p) / f_231;
	_beta = auxBarycentricFunction(v3, v1, p) / f_312;
	_gamma = auxBarycentricFunction(v1, v2, p) / f_123;

	return Vector3f(_alpha, _beta, _gamma);
}

/**
 * This is an auxiliary function required to compute the barycentric coordinates
 * for a point. It's an implementation of the technique outlined here
 * http://www.cs.caltech.edu/courses/cs171/barycentric.pdf
 * and provided as a course resource
 */
float Triangle2Di::auxBarycentricFunction(Vector2i va, Vector2i vb, Vector2i v) {
	return (va[Y] - vb[Y])*v[X] + (vb[X] - va[X])*v[Y] +
			va[X]*vb[Y] - vb[X]*va[Y];
}


bool Triangle2Di::contains(Vector2i p) {

	Vector3f _bar = getBarycentricCoordinates(p);
	if ((_bar[0] >= 0.0f && _bar[0] <= 1.0f ) &&
			(_bar[1] >= 0.0f && _bar[1] <= 1.0f ) &&
			(_bar[2] >= 0.0f && _bar[2] <= 1.0f ))
		return true;
	return false;
}

float Triangle2Di::interpolate(
		Vector2i p, float f1, float f2, float f3) {
	Vector3f c = getBarycentricCoordinates(p);
	return (c[0] * f1 + c[1] * f2 + c[2] * f3);
}

Color Triangle2Di::interpolate(
		Vector2i p, Color c1, Color c2, Color c3) {
	Vector3f c = getBarycentricCoordinates(p);
	int r = (int) (c[0] * c1.getRed() + c[1] * c2.getRed() + c[2] * c3.getRed());
	int g = (int) (c[0] * c1.getGreen() + c[1] * c2.getGreen() + c[2] * c3.getGreen());
	int b = (int) (c[0] * c1.getBlue() + c[1] * c2.getBlue() + c[2] * c3.getBlue());
	return Color((byte) r, (byte) g, (byte) b);
}

Vector3f Triangle2Di::interpolate(Vector2i p,
		const Vector3f* v1, const Vector3f* v2, const Vector3f* v3) {
	Vector3f c = getBarycentricCoordinates(p);
	float x = c[0] * v1->get(0) + c[1] * v2->get(0) + c[2] * v3->get(0);
	float y = c[0] * v1->get(1) + c[1] * v2->get(1) + c[2] * v3->get(1);
	float z = c[0] * v1->get(2) + c[1] * v2->get(2) + c[2] * v3->get(2);
	return Vector3f(x, y, z);
}

