#
using namespace std;
#include <iostream>
#include <fstream>
#include <string.h>
#include "TriangleMesh.h"

const Color TriangleMesh::DEFAULT_COLOR(255, 255, 0);

//Triangle
void Triangle::computeNormal() {

	Vector3f va = *_v2->getVector();
	va -= *_v1->getVector();
	Vector3f vb = *_v3->getVector();
	vb -= *_v1->getVector();

	_normal = Vector3f::crossProduct(va, vb);
	_normal.normalize();
}

void Triangle::computeColor() {
	float scale = Vector3f::dotProduct(_normal, Environment::light);
	scale += Environment::globalLightingConstant;
	this->_color = Color(scale);
}

//Vertex
void Vertex::computeNormal() {
	for (vector<int>::const_iterator i = _triangles.begin();
			i < _triangles.end(); i++) {
		_normal += _parent->getTriangle(*i)->getNormal();
	}
	_normal.normalize();
}

void Vertex::computeColor() {
	float scale = Vector3f::dotProduct(_normal, Environment::light);
	scale += Environment::globalLightingConstant;
	this->_color = Color(scale);
}

//TriangleMesh
void TriangleMesh::update() {
	computeTriangleNormals();
	computeTriangleColors();
	computeVertexNormals();
	computeVertexColors();
}

void TriangleMesh::computeTriangleNormals() {
	for (int i = 0; i < _trig.size(); i++ ) {
		_trig[i].computeNormal();
	}
}

void TriangleMesh::computeTriangleColors() {
	for (int i = 0; i < _trig.size(); i++ ) {
		_trig[i].computeColor();
	}
}

void TriangleMesh::computeVertexNormals() {
	for (int i = 0; i < _v.size(); i++) {
		_v[i].computeNormal();
	}
}

void TriangleMesh::computeVertexColors() {
	for (int i = 0; i < _v.size(); i++) {
		_v[i].computeColor();
	}
}

//function to read in a trianglemesh from a file
void TriangleMesh::loadFile(char * filename)
{
	ifstream f(filename);

	if (f == NULL) {
		cerr << " Failed reading polygon data file " << filename << endl;
		//exit(1);
	}

	char buf[1024];
	char header[100];
	float x,y,z;
	float xmax,ymax,zmax,xmin,ymin,zmin;
	int v1, v2, v3, n1, n2, n3;

	xmax =-10000; ymax =-10000; zmax =-10000;
	xmin =10000; ymin =10000; zmin =10000;
	Vector3f av;
	av[0] = av[1] = av[2] = 0.f;

	while (!f.eof()) {
		    f.getline(buf, sizeof(buf));
		    sscanf(buf, "%s", header);

		    if (strcmp(header, "v") == 0) {
			sscanf(buf, "%s %f %f %f", header, &x, &y, &z);

			_v.push_back(Vertex(Vector3f(x,y,z), this));
			av[0] += x; av[1] += y; av[2] += z;

			if (x > xmax) xmax = x;
			if (y > ymax) ymax = y;
			if (z > zmax) zmax = z;

			if (x < xmin) xmin = x;
			if (y < ymin) ymin = y;
			if (z < zmin) zmin = z;
		    }
		    else if (strcmp(header, "f") == 0) {
			sscanf(buf, "%s %d %d %d", header, &v1, &v2, &v3);

			Triangle trig(&_v[v1-1], &_v[v2-1], &_v[v3-1], this);
			_trig.push_back(trig);
			_v.at(v1-1)._triangles.push_back(_trig.size()-1);
			_v.at(v2-1)._triangles.push_back(_trig.size()-1);
			_v.at(v3-1)._triangles.push_back(_trig.size()-1);
		    }
 	}

	_xmin = xmin; _ymin = ymin; _zmin = zmin;
	_xmax = xmax; _ymax = ymax; _zmax = zmax;

	float range;
	if (xmax-xmin > ymax-ymin) range = xmax-xmin;
	else range = ymax-ymin;

	cout << "Trig " << _trig.size() << " vertices " << _v.size() << endl;
	f.close();
}

void TriangleMesh::translate(const Vector3f* translation) {
	for (vector<Vertex>::iterator i = _v.begin();
	           i != _v.end(); i++) {
		i->_vector += *translation;
	}
}
