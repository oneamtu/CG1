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
class Color;

#include "Geometry.h"
#include "Math.h"
#include "Vector.h"
#include "TriangleMesh.h"

using namespace MyMath;

class Color {
	friend class Image;
private:
	byte red, green, blue;
public:
	Color() :
		red(0), green(0), blue(0) {
	}
	Color(byte r, byte g, byte b) :
		red(r), green(g), blue(b) {
	}
	ostream & operator<<(ostream & stream) {
		stream << red << ' ' << green << ' ' << blue << ' ';
	}
};

class Image {

public:

    const static int height = 640;
    const static int width = 640;
    const static float upp = 2.0f/width;//units per pixel
    const static float fov = 0.524f;

public:
    Image() : focalLength(1.0f / tan(fov/2)) {}

    Vector2f projectVertexOntoPlane(const Vector3f v);
    Vector2i projectVertexIntoPixel(const Vector3f v);
    vector<Vector2i> projectTriangleIntoPixels(
    		Vector3f v1, Vector3f v2, Vector3f v3);
    Vector2i convertFromProjectionPlaneToImage(Vector2f v);
    void projectVertices(const vector<Vector3f> * vertices);
    void projectTriangleMesh(TriangleMesh trig);
    bool containsPoint(Vector2i p);
    void addPixel(Vector2i p, Color c);

    void output(const char * filename);

    const Color* getImageArray() const;


private:
    Color _image[height * width];
    float focalLength;

};

/*
 * Image getters
 */
inline const Color* Image::getImageArray() const { return _image; }

#endif /* IMAGE_H_ */
