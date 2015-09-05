#ifndef __BOARD_H
#define __BOARD_H

#include "common.h"
#include "square.h"
#include "api.h"
class Board {
private:
	const int Width;
	const int Height;
	Location loc;

public:
	static Square board[9][9];

public:
	Board();
	~Board();

	void DrawBoard();

	Location get_loc(){ return loc; }
};

#endif // __BOARD_H