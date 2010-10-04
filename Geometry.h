#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <assert.h>
#include "Vector.h"
#include "Common.h"

class Triangle;

enum Axis {
    X = 0, Y = 1, Z = 2
};

class Triangle {
friend class TriangleMesh;

	int _vertex[3];
public:

    Triangle(int v1, int v2, int v3) {
        _vertex[0] = v1;
        _vertex[1] = v2;
        _vertex[2] = v3;

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
