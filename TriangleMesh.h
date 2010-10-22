#ifndef _TRIANGLEMESH_H
#define _TRIANGLEMESH_H

#include <cmath>
#include <vector>

class TriangleMesh;
class Triangle;

#include "Geometry.h"
#include "Image.h"
#include "Vector.h"
using namespace MyMath;

enum Shading{
	FLAT = 0,
	GOURAUD = 1,
	PHONG = 2
};

class Triangle {
friend class TriangleMesh;

private:
	const TriangleMesh* _parent;
	Vector3f _normal;
	int _v1,_v2,_v3;
public:

    Triangle(int v1, int v2, int v3, const TriangleMesh* parent) {
        _v1 = v1;
        _v2 = v2;
        _v3 = v3;
        _parent = parent;
        computeNormal();
    }

    void computeNormal();
    void computeColor();
};


class TriangleMesh
{

private:
	vector <Vector3f> _v;
	vector <Triangle> _trig;
	float _xmax, _xmin, _ymax, _ymin, _zmin, _zmax;
	Shading _shading;

public:
	TriangleMesh(char * filename) : _shading(FLAT){ loadFile(filename);}
	TriangleMesh() {}

	void loadFile(char * filename);

	int trigNum() { return _trig.size() ;}

	void translate(Vector3f translation);

	void getTriangleVertices(int i, Vector3f & v1, Vector3f & v2, Vector3f & v3) {
		v1 = _v[_trig[i]._v1];
		v2 = _v[_trig[i]._v2];
		v3 = _v[_trig[i]._v3];
	}

	Vector3f getVertex(int i) const {return _v[i];}

	const vector <Vector3f> * getVertices() const { return &_v;}
};

#endif //TriangleMesh_DEFINED
