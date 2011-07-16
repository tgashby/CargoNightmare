/*
	Point2D class, deals with points in space, and the directions between them.

	Direction is either positive or negative, magnitude is unimportant.

	Author:		Taggart Ashby
*/

#ifndef _POINT_2D_
#define _POINT_2D_

#include <algorithm>

class Point2D {
public:
	Point2D(int xPos, int yPos) {
		x = xPos;
		y = yPos;

		xDir = 1;
		yDir = 1;
	}

	Point2D(Point2D& rhs) {
		x = rhs.x;
		y = rhs.y;
		xDir = rhs.xDir;
		yDir = rhs.yDir;
	}

	//X manipulation
	int getX() const { return x; }
	void setX(int val) { x = val; }
	float getXDir() const { return xDir; }
	void setXDir(float val) { xDir = val; }
	
	//Y manipulation
	int getY() const { return y; }
	void setY(int val) { y = val; }
	float getYDir() const { return yDir; }	
	void setYDir(float val) { yDir = val; }

	//Returns a point with the same coordinates as the prior point, but facing
	//the point desired
	Point2D setDirTo(Point2D&);

private:
	int x, y;
	float xDir, yDir;
};

#endif
