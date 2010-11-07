/*
 * Image.h
 *
 *  Created on: Sep 30, 2010
 *      Author: oneamtu
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "Common.h"
#include <vector>
#include <fstream>

class Image;

#include "Color.h"
#include "Geometry.h"
#include "Math.h"
#include "Vector.h"
#include "TriangleMesh.h"
#include "Camera.h"

using namespace MyMath;

class Image {

public:
    const static int height = 400;
    const static int width = 400;
    const static float Z_BUFFER_MAX = 10000.0f;

private:
    Color _image[height * width];
    float _zBuffer[height * width];
	const Camera* _camera;

public:
    Image(const Camera* c) {
    	this->_camera = c;
    	resetZBuffer();
    }

    Vector3f projectVertexIntoViewVolume(const Vector3f* v);
    Vector2i projectVertexIntoPixel(const Vector3f* v);
    vector<Vector2i> projectTriangleIntoPixels(
    		const Triangle* t, Shading shading);
    Vector2i convertFromViewVolumeToImage(const Vector3f* v);
    void projectVertices(const vector<Vertex> * vertices);
    void projectTriangleMesh(const TriangleMesh* trig);

    bool containsPoint(Vector2i p);
    void addPixel(Vector2i p, Color c);

    void output(const char * filename);

    void resetZBuffer() {
    	for (int i = 0; i < width * height; i++)
    		_zBuffer[i] = Z_BUFFER_MAX;
    }

    const Color* getImageArray() const {
    	return _image;
    }

};

#endif /* IMAGE_H_ */
