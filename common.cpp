#include "common.h"
#include "image.h"
#include "mouse.h"
#include "board.h"
#include "debug.h"

HWND hWnd;
MSG Message;

Image* image = new Image();
Mouse* mouse = new Mouse();
Debug* debug = new Debug();

Player* turn;

Location CooToPxl(Location coo){
	Location tmp;

	tmp.x = coo.x * 65 + Board::loc.x;
	tmp.y = coo.y * 65 + Board::loc.y;

	return tmp;
}

Location PxlToCoo(Location pxl){
	Location tmp;
	Location r;

	tmp.x = (pxl.x - Board::loc.x) / 65;
	tmp.y = (pxl.y - Board::loc.y) / 65;

	r.x = (pxl.x - Board::loc.x) % 65;
	r.y = (pxl.y - Board::loc.y) % 65;

	if (!CheckCooRange(tmp))
		tmp.x = tmp.y = -1;

	if (!CheckCooRangeAdditional(r))
		tmp.x = tmp.y = -1;

	/*
	if (tmp.x < 0 || tmp.x > 8)
		tmp.x = -1;
	if (tmp.y < 0 || tmp.y > 8)
		tmp.y = -1;
	*/
	if (60 <= r.x && r.x <= 64)
		tmp.x = -1;
	if (60 <= r.y && r.y <= 64)
		tmp.y = -1;

	return tmp;
}

bool CheckCooRange(Location coo){
	if (coo.x < 0 || coo.x > 8)
		return false;

	if (coo.y < 0 || coo.y > 8)
		return false;

	return true;
}

bool CheckCooRangeAdditional(Location coo){
	if (coo.x < 0 || coo.y < 0)
		return false;

	return true;
}

int __get_IntSquare(int n){
	return n * n;
}

/*
bool operator==(Location &loc1, Location &loc2){
	if (loc1.x == loc2.x && loc2.y == loc2.y)
		return true;

	return false;
}
*/