#include "common.h"
#include "board.h"

Location CooToPxl(Location coo){
	Location tmp;

	tmp.x = coo.x * 65 + Board::loc.x;
	tmp.y = coo.y * 65 + Board::loc.y;
	
	return tmp;
}

Location PxlToCoo(Location pxl){
	Location tmp;

	int rx = (pxl.x - Board::loc.x) % 65;
	int ry = (pxl.x - Board::loc.y) % 65;

	tmp.x = (pxl.x - Board::loc.x) / 65;
	tmp.y = (pxl.y - Board::loc.y) / 65;

	if (tmp.x < 0 || tmp.x > 8)
		tmp.x = -1;
	if (tmp.y < 0 || tmp.y > 8)
		tmp.y = -1;
	if (60 <= rx && rx <= 64)
		tmp.x = -1;
	if (60 <= ry && ry <= 64)
		tmp.y = -1;

	return tmp;
}