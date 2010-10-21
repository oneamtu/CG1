#ifndef _MYMATH_H
#define _MYMATH_H
/*
 * @author Octavian Neamtu
 *
 * header file that contains most common math definitions that are not
 * included in standard libraries
 */

namespace MyMath {

static const float FLOAT_ERROR = .0001f;

static bool isZero(float f) {
	if (f <= FLOAT_ERROR || f >= -FLOAT_ERROR) {
		return true;
	}
	return false;
}

static int max(int x, int y) {
	if (x > y) return x;
	return y;
}

static int min(int x, int y) {
	if (x < y) return x;
	return y;
}

static int max(int x, int y, int z) {
	return max(max(x, y), z);
}

static int min(int x, int y, int z) {
	return min(min(x, y), z);
}

}

#endif //_MYMATH_H
