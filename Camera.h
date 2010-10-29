#ifndef _CAMERA_H
#define _CAMERA_H

#include "Matrix.h"

class Camera {

private:
	Vector3f _location;
	//RotationMatrix _m;
	Matrix4f _perspectiveToParallel;
	float _far, _near; //clipping distances
	float _left, _right, _top, _bottom; //view frustum near plane bounds
	float _focalLength;
	float _fov;
	float _width;

public:
	static const float DEFAULT_WIDTH = 2.0f;
	static const float DEFAULT_FAR = -2000.0f;
	Camera(float fov, Vector3f l) :
		_fov(fov), _focalLength(1.0f / tan(_fov/2)),
		_near(-_focalLength), _far(DEFAULT_FAR),
		_width(DEFAULT_WIDTH),
		_top(_width/2), _right(_width/2),
		_bottom(-_width/2), _left(-_width/2){
		_perspectiveToParallel =
				Matrix4f::perspectiveToParallelTranform(
						_right, _left, _top, _bottom, _near, _far);
		_location = l;
	}

	float getFocalLength() const {return _focalLength;}
	Vector3f project(Vector3f p) const {
		return Matrix4f::prod(_perspectiveToParallel, p);
	}
};

#endif //_CAMERA_H
