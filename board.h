#ifndef __BOARD_H
#define __BOARD_H

#include "api.h"

class Board {
private:
	const int Size;
	const int Width;
	const int Height;

	IDirect3DTexture9* pBoardTexture;

public:
	static Location loc;
	static Square*** board;

public:
	Board();
	Board(IDirect3DTexture9*);
	~Board();

	void Init();
	void Draw();
};

#endif // __BOARD_H