#ifndef _CAMERA_H
#define _CAMERA_H

#include "Matrix.h"

class Camera {

private:
	Vector3f _location;
	//RotationMatrix _m;
	Matrix4f _perspectiveToParallel;
	float _far; //clipping distances
	float _focalLength;
	float _fov;
	float _width;//width of the projection screen

public:
	static const float DEFAULT_WIDTH = 2.0f;
	static const float DEFAULT_FAR = 1000.0f;
	Camera(float fov, Vector3f l) :
		_fov(fov), _focalLength(1.0f / tan(fov/2)),
		_far(DEFAULT_FAR),
		_width(DEFAULT_WIDTH) {
		_perspectiveToParallel =
				Matrix4f::perspectiveToParallelTranform(
						_focalLength, _far);
		_location = l;
	}

	float getFocalLength() const {return _focalLength;}
	const Vector3f* getLocation() const {return &_location;}
        //not used
	Vector3f project(const Vector3f *p) const {
		return Matrix4f::prod(_perspectiveToParallel, p);
	}
};

#endif //_CAMERA_H
