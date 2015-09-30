#include "common.h"
#include "image.h"
#include "mouse.h"
#include "board.h"
#include "square.h"
#include "debug.h"

HWND hWnd;
MSG Message;

Image* image = new Image();
Mouse* mouse = new Mouse();
Debug* debug = new Debug();

Player* turn;

Location CooToPxl(int x, int y, int s){
	Location tmp, stdd;

	if (s == Board::SIZE)
		stdd = Board::loc;
	else{
		stdd.x = Board::itsloc.x + (Square::SIZE >> 1);
		stdd.y = Board::itsloc.y + (Square::SIZE >> 1);
	}

	tmp.x = x * 65 + stdd.x;
	tmp.y = y * 65 + stdd.y;

	//tmp.x = coo.x * 65 + Board::loc.x;
	//tmp.y = coo.y * 65 + Board::loc.y;

	return tmp;
}

Location CooToPxl(Location coo, int s){
	return CooToPxl(coo.x, coo.y, s);
}

Location PxlToCoo(Location pxl, int s){
	Location q, r;
	Location stdd = (s == Board::SIZE)? Board::loc: Board::itsloc;

	q.x = (pxl.x - stdd.x) / 65;
	q.y = (pxl.y - stdd.y) / 65;
	//tmp.x = (pxl.x - Board::loc.x) / 65;
	//tmp.y = (pxl.y - Board::loc.y) / 65;

	r.x = (pxl.x - stdd.x) % 65;
	r.y = (pxl.y - stdd.y) % 65;

	//r.x = (pxl.x - Board::loc.x) % 65;
	//r.y = (pxl.y - Board::loc.y) % 65;

	if (!CheckCooRange(q, s))
	//if (!CheckCooRange(q))
		q.x = q.y = -1;

	if (!CheckCooRangeAdditional(r))
		q.x = q.y = -1;
	/*
	if (q.x < 0 || q.x > 8)
		q.x = -1;
	if (q.y < 0 || q.y > 8)
		q.y = -1;
	*/
	if (60 <= r.x && r.x <= 64)
		q.x = -1;
	if (60 <= r.y && r.y <= 64)
		q.y = -1;

	return q;
}

bool CheckCooRange(Location coo, int s){
//bool CheckCooRange(Location coo){
	if (coo.x < 0 || coo.x > s - 1)
	//if (coo.x < 0 || coo.x > Board::SIZE - 1)
		return false;

	if (coo.y < 0 || coo.y > s - 1)
	//if (coo.y < 0 || coo.y > Board::SIZE - 1)
		return false;

	return true;
}

bool CheckCooRangeAdditional(Location coo){
	if (coo.x < 0 || coo.y < 0)
		return false;

	return true;
}

/*
bool operator==(Location &loc1, Location &loc2){
	if (loc1.x == loc2.x && loc2.y == loc2.y)
		return true;

	return false;
}
*/