#ifndef _COLOR_H
#define _COLOR_H

#include "Common.h"
#include <iostream>

class Color {
private:
	byte red, green, blue;
public:
	static const byte MAX = 255;
	static const float MAXF = 254.9f;
	Color() :
		red(0), green(0), blue(0) {
	}
	Color(byte r, byte g, byte b) :
		red(r), green(g), blue(b) {
	}
	//grayscale
	Color(float f) {
		if (f >= 1.0f) f = 1.0f;
		red = blue = green = (byte) (MAXF * f);
	}
	ostream & operator<<(ostream & stream) {
		stream << red << ' ' << green << ' ' << blue << ' ';
	}
	int getRed() const {return (int) red;}
	int getGreen() const {return (int) green;}
	int getBlue() const {return (int) blue;}
};

#endif //_COLOR_H
