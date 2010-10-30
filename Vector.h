/*
 * Vector.h
 *
 *  Created on: Oct 4, 2010
 *      Author: Octavian Neamtu
 *
 *  Generic vector class with specialized classes for
 *  some commonly used vectors (3f, 2f, 2i)
 */

#ifndef _VECTOR_H
#define _VECTOR_H
#include <assert.h>
#include <iostream>
#include <fstream>
#include <math.h>

#include "Common.h"

class Vector3f;

/*
 * class Vector
 *
 * generic class that implements usual operations
 * on an N-dimensional vector of type T
 */
template<typename T, int N>
class Vector {

protected:
	T _item[N];

public:

	T & operator [](int i) {
		assert(i < N);
		return _item[i];
	}

	Vector(T * array) : _item(array) {
	}

	Vector() {
		for (int i = 0; i < N; i++) {
			_item[i] = 0;
		}
	}

//	Vector(const Vector &obj) {
//		for (int i = 0; i < N; i++) {
//			_item[i] = obj.getElementAt(i);
//		}
//	}

	Vector & operator =(const Vector & obj) {
		for (int i = 0; i < N; i++) {
			_item[i] = obj.getElementAt(i);
		}
		return *this;
	}

	Vector & operator +=(const Vector & obj) {
		for (int i = 0; i < N; i++) {
			_item[i] += obj.getElementAt(i);
		}
		return *this;
	}

	Vector & operator -=(const Vector & obj) {
		for (int i = 0; i < N; i++) {
			_item[i] -= obj.getElementAt(i);
		}
		return *this;
	}

	ostream & operator <<(ostream & stream) {
		for (int i = 0; i < N; i++) {
			stream << _item[i] << ' ';
		}
	}

	const T getElementAt(int i) const {
		return _item[i];
	}

	const T get(int i) const {
		return _item[i];
	}

};

/*
 * specialized vector classes
 */

class Vector3f : public Vector<float, 3> {

public:

	Vector3f(float x, float y, float z) : Vector(){
		_item[0] = x;
		_item[1] = y;
		_item[2] = z;
	}

	Vector3f() : Vector(){
	}

	float length() const {
		return sqrt(_item[0]*_item[0] +
				_item[1]*_item[1] +
				_item[2]*_item[2]);
	}

	void normalize(){
		float l = length();
		_item[0] = _item[0]/l;
		_item[1] = _item[1]/l;
		_item[2] = _item[2]/l;
	}

	static Vector3f crossProduct(Vector3f v1, Vector3f v2) {
		return Vector3f(v1[1]*v2[2]-v1[2]*v2[1],
				v1[2]*v2[0]-v1[0]*v2[2],
				v1[0]*v2[1]-v1[1]*v2[0]);
	}

	static float dotProduct(Vector3f v1, Vector3f v2) {
		return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
	}

};

class Vector2f : public Vector<float, 2> {

public:

	Vector2f(float x, float y) : Vector(){
		_item[0] = x;
		_item[1] = y;
	}

	Vector2f() : Vector() {
	}
};

class Vector2i : public Vector<int, 2> {

public:

	Vector2i(int x, int y) : Vector(){
		_item[0] = x;
		_item[1] = y;
	}

	Vector2i() : Vector() {
	}

	int getX() const { return _item[0]; }
	int getY() const { return _item[1]; }

};

#endif //_VECTOR_H
