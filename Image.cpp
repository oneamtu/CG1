/*
 * Image.cpp
 *
 *  Created on: Oct 1, 2010
 *      Author: oneamtu
 */

#include <stdlib.h>

#include "Image.h"
#include "MyMath.h"


Vector3f Image::projectVertexIntoViewVolume(const Vector3f *v) {

    float n = _camera->getFocalLength();
    float f = 80.0f;

    //perspective projection
    //transformation for z from lecture notes
    //this is faster and simpler than the matrix form
    //but the matrix form would be better if using
    //hardware pipes
    float _ratio = -_camera->getFocalLength() / v->get(Z);
    float _x = _ratio * v->get(X);
    float _y = _ratio * v->get(Y);
    float _z = f/(f-n)* (-v->get(Z)) - f*n/(f-n);
    
    return Vector3f(_x, _y, _z);
//    Vector3f _v = _camera->project(v);
//    return _v;
}


Vector2i Image::projectVertexIntoPixel(const Vector3f *v) {

    Vector3f pv = projectVertexIntoViewVolume(v);
    return convertFromViewVolumeToImage(&pv);
}

Vector2i Image::convertFromViewVolumeToImage(const Vector3f *v) {

	int _x = (int) (v->get(X) * width/2);
	int _y = (int) (v->get(Y) * height/2);

	_x += (int) (width/2);
	_y += (int) (height/2);

	//we flip the y because in the world system the y axis points up
	//in the image in points down
	_y = height - _y;

	return Vector2i(_x, _y);
}

vector<Vector2i> Image::projectTriangleIntoPixels(
		const Triangle *t, Shading shading) {

	vector <Vector2i> _pixels;
	Vector3f n;

	const vector<const Vertex *> v = t->getVertices();
	const Vector3f *v1, *v2, *v3;
	v1 = v[0]->getVector();
	v2 = v[1]->getVector();
	v3 = v[2]->getVector();

	Vector3f vv1 = projectVertexIntoViewVolume(v1);
	Vector3f vv2 = projectVertexIntoViewVolume(v2);
	Vector3f vv3 = projectVertexIntoViewVolume(v3);

	Vector2i pv1 = projectVertexIntoPixel(v1);
	Vector2i pv2 = projectVertexIntoPixel(v2);
	Vector2i pv3 = projectVertexIntoPixel(v3);
	Triangle2Di t2d(pv1, pv2, pv3);

	for (int i = t2d.leftBound(); i < t2d.rightBound(); i++) {
		for (int j = t2d.bottomBound(); j < t2d.topBound(); j++) {
			Vector2i _p = Vector2i(i, j);
			if (t2d.contains(_p) && this->containsPoint(_p)) {
				//z-buffering
				float _z = t2d.interpolate(_p, vv1[Z], vv2[Z], vv3[Z]);
				if (_z < _zBuffer[_p[X] + height * _p[Y]]) {
					_zBuffer[_p[X] + height * _p[Y]] = _z;
					//shading
					switch (shading) {
					case NONE:
					  //use default color
						this->addPixel(_p, TriangleMesh::DEFAULT_COLOR);
						break;
					case FLAT:
					  //use color of triangle
						this->addPixel(_p, t->getColor());
						break;
					case GOURAUD:
					  //interpolate color of vertices
						this->addPixel(_p, t2d.interpolate(_p,
								v[0]->getColor(), v[1]->getColor(), v[2]->getColor()));
						break;
					case PHONG:
					  //interpolate normals and compute color
						n = t2d.interpolate(_p,
								v[0]->getNormal(), v[1]->getNormal(), v[2]->getNormal());
						n.normalize();
						this->addPixel(_p, Color(Vector3f::dotProduct(n, Environment::light)
						+ Environment::globalLightingConstant));
						break;
					default:
						this->addPixel(_p, TriangleMesh::DEFAULT_COLOR);
						break;
					}
				}
			}
		}
	}
	return _pixels;
}

//projects a bunch of vertices on the screen
//useful for debugging
void Image::projectVertices(const vector<Vertex> * vertices) {

   for (vector<Vertex>::const_iterator i = vertices->begin();
           i != vertices->end(); i++) {
       Vector2i p = projectVertexIntoPixel(&(*i->getVector()));
       if (this->containsPoint(p)) {
    	   addPixel(p, Color(255,255,255));
       }
   }
}

void Image::projectTriangleMesh(const TriangleMesh *triangleMesh) {

	for (int i = 0; i < triangleMesh->trigNum(); i++ ) {
		projectTriangleIntoPixels(
				triangleMesh->getTriangle(i),
				triangleMesh->getShading());
	}
}

void Image::addPixel(Vector2i p, Color c) {
	_image[p[X] + width * p[Y]] = c;
}


bool Image::containsPoint(Vector2i p) {
	if (p[X] >= 0 && p[X] < width &&
			p[Y] >=0 && p[Y] < height) {
		return true;
	}
	return false;
}

void Image::output(const char * filename) {

    ofstream f(filename, ios::out);
    if (f == NULL) {
        cerr << " Failed to create/open output file " << filename << endl;
        exit(1);
    }
    f<<"P3"<<endl;
    f<<width<<" "<<height<<endl;
    f<<255<<endl;
    for (int i = 0; i < height*width; i++) {
        f<<(int)_image[i].getRed()<<' '
        		<<(int)_image[i].getGreen()<<' '
        		<<(int)_image[i].getBlue()<<' ';
        if ((i-1)%width == 0) {
            f<<endl;
        }
    }
}
