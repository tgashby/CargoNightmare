#include "Point2D.h"

Point2D Point2D::setDirTo(Point2D& to) {
	Point2D from = *this;

	//Figure out the direction to the desired point
	to.getX() < from.getX() ? from.setXDir(-1) : from.setXDir(1);
	to.getY() < from.getY() ? from.setYDir(-1) : from.setYDir(1);

	//If the Xs or Ys are the same, set their direction to 0
	if(to.getX() == from.getX())
		from.setXDir(0);

	if(to.getY() == from.getY())
		from.setYDir(0);

	return from;
}