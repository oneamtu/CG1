#ifndef _TRIANGLEMESH_H
#define _TRIANGLEMESH_H

#include <cmath>
#include <vector>

class TriangleMesh;
class Triangle;
class Vertex;

#include "Geometry.h"
#include "Color.h"
#include "Vector.h"
#include "Environment.h"
using namespace MyMath;

enum Shading{
	NONE = 0,
	FLAT = 1,
	GOURAUD = 2,
	PHONG =3
};

//unit class of a TriangleMesh
//holds pointers to its vertices and
//the normal and color of the polygon
class Triangle {
friend class TriangleMesh;

private:
	const TriangleMesh* _parent;
	Vector3f _normal;
	const Vertex *_v1,*_v2,*_v3;
	Color _color;
public:

    Triangle(const Vertex* v1,
    		const Vertex* v2,
    		const Vertex* v3,
    		const TriangleMesh* parent) :
    _v1(v1), _v2(v2), _v3(v3), _parent(parent) {}

    void computeNormal();
    void computeColor();

    //getters
    const Color getColor() const {return _color;}
    const Vector3f getNormal() const {return _normal;}
    const vector<const Vertex*> getVertices() const {
    	vector <const Vertex* > v;
    	v.push_back(_v1);
    	v.push_back(_v2);
    	v.push_back(_v3);
    	return v;
    }

};

//unit class of TriangleMesh
//holds a 3d vector of its position 
//also the interpolated normal of its polygons
//and computed color
class Vertex {
friend class TriangleMesh;
private:
	const TriangleMesh* _parent;
	Vector3f _vector;
	Vector3f _normal;
	vector <int> _triangles;
	Color _color;

public:
	Vertex(Vector3f v, const TriangleMesh* parent) :
	_parent(parent), _vector(v){}
	Vertex() {}

	void computeNormal();
	void computeColor();

        //getters
	const Vector3f* getVector() const { return &_vector;}
	const Color getColor() const {return _color;}
	const Vector3f* getNormal() const { return &_normal;}

};

//holds all the vertices and triangles
class TriangleMesh {

private:
	vector <Vertex> _v;
	vector <Triangle> _trig;
	float _xmax, _xmin, _ymax, _ymin, _zmin, _zmax;
	Shading _shading;

public:
	const static Color DEFAULT_COLOR;

public:
	TriangleMesh(char *filename) : _shading(PHONG){ loadFile(filename);}
	TriangleMesh() {}

	void loadFile(char *filename);

	int trigNum() const { return _trig.size() ;}

	void translate(const Vector3f* translation);
	void update();

	void computeTriangleNormals();
	void computeTriangleColors();
	void computeVertexNormals();
	void computeVertexColors();

        //getters and setters
	const Triangle* getTriangle(int i) const { return &_trig[i]; }
	const Vertex* getVertex(int i) const {return &_v[i];}
	const vector <Vertex> * getVertices() const { return &_v;}
	const Shading getShading() const { return _shading;}
	const vector<const Vertex*> getTriangleVertices(int i) {
		return _trig[i].getVertices();
	}

	void setShading(Shading s) {_shading = s;}
};

#endif //_TRIANGLEMESH_DEFINED
