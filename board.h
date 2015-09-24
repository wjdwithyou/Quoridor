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

	Location __get_centerLoc() const;

	int get_Size() const{ return Size; }
	int get_Width() const{ return Width; }
	int get_Height() const{ return Height; }
};

#endif // __BOARD_H