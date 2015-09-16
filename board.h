#ifndef __BOARD_H
#define __BOARD_H

#include <d3d9.h>
#include "common.h"

class Square;

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
	void Draw() const;
};

#endif // __BOARD_H