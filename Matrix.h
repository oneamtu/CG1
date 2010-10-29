#ifndef _MATRIX_H
#define _MATRIX_H

#include "Vector.h"

class Matrix4f;
class RotationMatrix;


class Matrix4f {

private:
	float _item[4][4];

public:
	Matrix4f() {}

	void set(int i, int j, float f){
		_item[i][j] = f;
	}

	float get(int i, int j) const {return _item[i][j];}

	static Vector3f prod(Matrix4f m, Vector3f v) {
		float x, y, z, w;

		w = m.get(3, 0) * v.get(0) + m.get(3, 1) * v.get(1)
				+ m.get(3, 2) * v.get(2) + m.get(3, 3);
		x = m.get(0, 0) * v.get(0) + m.get(0, 1) * v.get(1)
				+ m.get(0, 2) * v.get(2) + m.get(0, 3);
		x = x/w;
		y = m.get(1, 0) * v.get(0) + m.get(1, 1) * v.get(1)
				+ m.get(1, 2) * v.get(2) + m.get(1, 3);
		y = y/w;
		z = m.get(2, 0) * v.get(0) + m.get(2, 1) * v.get(1)
				+ m.get(2, 2) * v.get(2) + m.get(2, 3);
		z = z/w;
		return Vector3f(x, y, z);
	}

	static Matrix4f perspectiveToParallelTranform(float r,
			float l, float t, float b, float n, float f) {
		Matrix4f m;
		m.set(0, 0, 2*n/(r-l));
		m.set(1, 1, 2*n/(t-b));
		m.set(0, 2, (r+l)/(r-l));
		m.set(1, 2, (t+b)/(t-b));
		m.set(2, 2, (f+n)/(n-f));
		m.set(2, 3, (2*f*n)/(n-f));
		m.set(3, 2, -1);
		return m;
	}

};

#endif //_MATRIX_H
