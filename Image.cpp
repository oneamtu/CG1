/*
 * Image.cpp
 *
 *  Created on: Oct 1, 2010
 *      Author: oneamtu
 */

#include <stdlib.h>

#include "Image.h"


MyMath::Vector2f Image::projectVertexOntoPlane(Vector3f v) {

    float _ratio = focalLength / v[Z];
    float _x = _ratio * v[X];
    float _y = _ratio * v[Y];
    return Vector2f(_x, _y);
}


MyMath::Vector2i Image::projectVertexIntoPixel(Vector3f v) {

    Vector2f _vf = projectVertexOntoPlane(v);
    int _x = (int) (_vf[X] * width);
    int _y = (int) (_vf[Y] * height);

    _x += (int) (width/2);
    _y += (int) (height/2);

    return Vector2i(_x, _y);
}

void Image::projectVertices(const vector<MyMath::Vector3f> * vertices) {

   for (vector<MyMath::Vector3f>::const_iterator i = vertices->begin();
           i != vertices->end(); i++) {
       Vector2i p = projectVertexIntoPixel(*i);
       if (this->containsPoint(p)) {
    	   _image[p[X] + width * p[Y]] = Pixel(255, 255, 255);
       }
   }
}

bool Image::containsPoint(MyMath::Vector2i p) {
	if (p[X] >= 0 && p[X] < width &&
			p[Y] >=0 && p[Y] < height) {
		return true;
	}
	return false;
}

void Image::output(const char * filename) {

    ofstream f(filename, ios::out);
    if (f == NULL) {
        cerr << " Failed reading polygon data file " << filename << endl;
        exit(1);
    }
    f<<"P3"<<endl;
    f<<width<<" "<<height<<endl;
    f<<255<<endl;
    for (int i = 0; i < height*width; i++) {
        f<<(int)_image[i].red<<' '<<(int)_image[i].green<<' '<<(int)_image[i].blue<<' ';
        if ((i-1)%width == 0) {
            f<<endl;
        }
    }
}
