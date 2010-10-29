/*
 * Image.cpp
 *
 *  Created on: Oct 1, 2010
 *      Author: oneamtu
 */

#include <stdlib.h>

#include "Image.h"
#include "MyMath.h"


Vector2f Image::projectVertexOntoPlane(Vector3f v) {

    //float _ratio = _camera->getFocalLength() / v[Z];
    //float _x = _ratio * v[X];
    //float _y = _ratio * v[Y];
	Vector3f _v = _camera->project(v);
    return Vector2f(_v[X], _v[Y]);
}


Vector2i Image::projectVertexIntoPixel(Vector3f v) {

    Vector2f _vf = projectVertexOntoPlane(v);

    return convertFromProjectionPlaneToImage(_vf);
}

Vector2i Image::convertFromProjectionPlaneToImage(Vector2f v) {
	int _x = (int) (v[X] * width);
	int _y = (int) (v[Y] * height);

	_x += (int) (width/2);
	_y += (int) (height/2);

	//we flip the y because in the world system the y axis points up
	//in the image in points down
	_y = height - _y;

	return Vector2i(_x, _y);
}

vector<Vector2i> Image::projectTriangleIntoPixels(
		Vector3f v1, Vector3f v2, Vector3f v3) {

	vector <Vector2i> _pixels;

	Vector2i pv1 = projectVertexIntoPixel(v1);
	Vector2i pv2 = projectVertexIntoPixel(v2);
	Vector2i pv3 = projectVertexIntoPixel(v3);
	Triangle2Di t(pv1, pv2, pv3);

	for (int i = t.leftBound(); i < t.rightBound(); i++) {
		for (int j = t.bottomBound(); j < t.topBound(); j++) {
			Vector2i point = Vector2i(i, j);
			if (t.contains(point)) {
				_pixels.push_back(point);
			}
		}
	}
	return _pixels;
}

void Image::projectVertices(const vector<Vector3f> * vertices) {

   for (vector<Vector3f>::const_iterator i = vertices->begin();
           i != vertices->end(); i++) {
       Vector2i p = projectVertexIntoPixel(*i);
       if (this->containsPoint(p)) {
    	   addPixel(p, Color(255,255,255));
       }
   }
}

void Image::projectTriangleMesh(TriangleMesh trig) {

	for (int i = 0; i < trig.trigNum(); i++ ) {
		Color c = trig.getTriangle(i).getColor();
		Vector3f v1, v2, v3;
		trig.getTriangleVertices(i, v1, v2, v3);
		vector<Vector2i> pixels = projectTriangleIntoPixels(v1, v2, v3);
		for (vector<Vector2i>::iterator j = pixels.begin(); j
				!= pixels.end(); j++) {
			if (this->containsPoint(*j)) {
				this->addPixel((*j), c);
			}
		}
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
