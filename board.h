#ifndef __BOARD_H
#define __BOARD_H

#include "square.h"
#include "api.h"

class Board {
private:
	const int Width;
	const int Height;

public:
	static Location loc;
	static Square board[9][9];

public:
	Board();
	~Board();

	void DrawBoard();
};

#endif // __BOARD_H