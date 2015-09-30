#include "point.h"
#include "board.h"

Point::Point(){}

Point::Point(int x, int y)
	: onBarStatus(d_none)
{
	pxloc = CooToPxl(x, y, Board::SIZE - 1);
}

Point::~Point(){}