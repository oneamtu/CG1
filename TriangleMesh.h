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


class TriangleMesh
{

private:
	vector <Vector3f> _v;
	vector <Triangle> _trig;
	float _xmax, _xmin, _ymax, _ymin, _zmin, _zmax;

public:
	TriangleMesh(char * filename) { loadFile(filename) ;};
	TriangleMesh() {};

	void loadFile(char * filename);

	int trigNum() { return _trig.size() ;}

	void translate(Vector3f translation);

	void getTriangleVertices(int i, Vector3f & v1, Vector3f & v2, Vector3f & v3) {
		v1 = _v[_trig[i]._vertex[0]];
		v2 = _v[_trig[i]._vertex[1]];
		v3 = _v[_trig[i]._vertex[2]];
	}
	const vector <Vector3f> * getVertices() const { return &_v;}
};

#endif //TriangleMesh_DEFINED
