#ifndef _Geometry_DEFINED
#define _Geometry_DEFINED

#include <iostream>
#include <fstream>

class Vector3f;
class Triangle;

using namespace std;

class Vector3f {

	float _item[3];

	public:

	float & operator [] (int i) {
		return _item[i];
    	}

	Vector3f(float x, float y, float z)
	{  _item[0] = x ; _item[1] = y ; _item[2] = z; };

	Vector3f() {};


	Vector3f & operator = (Vector3f & obj)
	{
		_item[0] = obj[0];
		_item[1] = obj[1];
		_item[2] = obj[2];

		return *this;
	};

	Vector3f & operator += (Vector3f & obj)
	{
		_item[0] += obj[0];
		_item[1] += obj[1];
		_item[2] += obj[2];

		return *this;
	};

	ostream & operator << (ostream & stream)
	{
		stream << _item[0] << ' ' << _item[1] << ' ' << _item[2] << ' ';
	};
};


class Triangle {
friend class TriangleMesh;

	int _vertex[3];
public:

	Triangle(int v1, int v2, int v3)
	{
		_vertex[0] = v1;  _vertex[1] = v2;  _vertex[2] = v3;

	};
};
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

#endif //_Geometry_DEFINED
