#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <assert.h>
#include "Vector.h"
#include "Color.h"
#include "Common.h"
#include "MyMath.h"

enum Axis {
    X = 0, Y = 1, Z = 2
};

class Rectangle2Di {

	Vector2i tl, tr, br, bl;

public:
	Rectangle2Di(int t, int r, int b, int l) :
		tl(t, l), tr(t, r), bl(b, l), br(b, r) {
	}

};

class Triangle2Di {

private:
	Vector2i v1, v2, v3;
	//barycentric constants
	float f_231, f_312, f_123;

	void computeBarycentricConstants();
	float auxBarycentricFunction(Vector2i va, Vector2i vb, Vector2i v);

public:
	Triangle2Di(Vector2i v1, Vector2i v2, Vector2i v3) :
		v1(v1), v2(v2), v3(v3),
		f_231(0.0f), f_312(0.0f), f_123(0.0f){
	}

	bool contains(Vector2i p);

	Vector3f getBarycentricCoordinates(Vector2i p);

	float interpolate(Vector2i p, float f1, float f2, float f3);
	Color interpolate(Vector2i p, Color c1, Color c2, Color c3);
	Vector3f interpolate(Vector2i p,
			const Vector3f* v1, const Vector3f* v2, const Vector3f* v3);

	int topBound() {
		return MyMath::max(v1[Y], v2[Y], v3[Y]);
	}

	int bottomBound() {
		return MyMath::min(v1[Y], v2[Y], v3[Y]);
	}

	int rightBound() {
		return MyMath::max(v1[X], v2[X], v3[X]);
	}

	int leftBound() {
		return MyMath::min(v1[X], v2[X], v3[X]);
	}

	Rectangle2Di getBoundingBox() {
		return Rectangle2Di(topBound(), rightBound(),
				bottomBound(), leftBound());
	}
};

#endif //_GEOMETRY_H
