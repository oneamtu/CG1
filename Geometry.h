#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <assert.h>
#include "Vector.h"
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

	Vector3f getBarycentricCoordinatesForPoint(Vector2i p);

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


/*
class Vector2i {

	int _item[2];

public:

	int & operator [](int i) {
		assert(i <= 2);
		return _item[i];
	}

	Vector2i(int x, int y) {
		_item[0] = x;
		_item[1] = y;
	}
};

class Vector2f {

	float _item[2];

	public:

	float & operator [] (int i) {
		assert(i <= 2);
		return _item[i];
    }

	Vector2f(float x, float y) {
        _item[0] = x;
        _item[1] = y;
    }

    Vector2f() {
    }


	Vector2f & operator = (Vector2f & obj)
	{
		_item[0] = obj[0];
		_item[1] = obj[1];

		return *this;
	};

	Vector2f & operator += (Vector2f & obj)
	{
		_item[0] += obj[0];
		_item[1] += obj[1];

		return *this;
	};

	ostream & operator << (ostream & stream)
	{
		stream << _item[0] << ' ' << _item[1] << ' ';
	}
};
/*
/*
float fmax(float f1,float f2, float f3) {
	float f = f1;

	if (f < f2) f = f2;
	if (f < f3) f = f3;

	return f;
};

float fmin(float f1,float f2, float f3) {
	float f = f1;

	if (f > f2) f = f2;
	if (f > f3) f = f3;

	return f;
};
/*/

#endif //_GEOMETRY_H
