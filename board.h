#ifndef __BOARD_H
#define __BOARD_H

#include "square.h"

class Board {
private:
	const int size;

public:
	Square board[9][9];

public:
	Board();
	~Board();

	void DrawBoard();
};

#endif // __BOARD_H