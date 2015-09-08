#ifndef __BOARD_H
#define __BOARD_H

#include "square.h"
#include "api.h"

class Board {
private:
	const int Size;
	const int Width;
	const int Height;

public:
	static Location loc;
	static Square** board;

public:
	Board();
	~Board();

	void Init();
	void Draw();
};

#endif // __BOARD_H