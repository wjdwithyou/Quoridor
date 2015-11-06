#include "common.h"
#include "image.h"
#include "sound.h"
#include "mouse.h"
#include "board.h"
#include "square.h"
#include "debug.h"

HWND hWnd;
MSG Message;

Image* image = new Image();
Sound* sound = new Sound();
Debug* debug = new Debug();

Mouse* g_mouse;

Pstat g_process;
Process** g_process_cur;
Process** g_process_list0;

Player** g_turn;

int ending = 0;	/////

Location CooToPxl(int x, int y, int s){
	Location tmp, stdd;

	stdd = (s == Board::SIZE)? Board::loc: Board::itsloc;

	tmp.x = x * 65 + stdd.x;
	tmp.y = y * 65 + stdd.y;

	return tmp;
}

Location CooToPxl(Location coo, int s){
	return CooToPxl(coo.x, coo.y, s);
}

Location PxlToCoo(Location pxl, int s){
	Location q, r;
	Location stdd;

	if (s == Board::SIZE)
		stdd = Board::loc;
	else{
		stdd.x = Board::itsloc.x - (Square::SIZE >> 1);
		stdd.y = Board::itsloc.y - (Square::SIZE >> 1);
	}

	q.x = (pxl.x - stdd.x) / 65;
	q.y = (pxl.y - stdd.y) / 65;

	r.x = (pxl.x - stdd.x) % 65;
	r.y = (pxl.y - stdd.y) % 65;

	if (!CheckCooRange(q, s))
		q.x = q.y = -1;

	if (!CheckCooRangeAdditional(r))
		q.x = q.y = -1;

	if (s == Board::SIZE){	// test
		if (60 <= r.x && r.x <= 64)		// square-square space
			q.x = -1;
		if (60 <= r.y && r.y <= 64)
			q.y = -1;
	}

	return q;
}

bool CheckCooRange(Location coo, int s){
	if (coo.x < 0 || coo.x > s - 1)
		return false;

	if (coo.y < 0 || coo.y > s - 1)
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