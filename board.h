#ifndef __BOARD_H
#define __BOARD_H

#include <d3d9.h>
#include "common.h"

class Square;
class Rectj;
class Point;

class Board {
private:
	IDirect3DTexture9* pBoardTexture;

public:
	const static int SIZE = 9;
	const static int WIDTH = 580;	// even only
	const static int HEIGHT = 580;	// even only

	static Location loc;	// 해상도에 따라 변경될 수 있으니 const X
	static Location itsloc;	// 해상도에 따라 변경될 수 있으니 const X

	static Square*** board;
	static Rectj*** vtc;
	static Rectj*** hrz;
	static Point*** its;

public:
	Board();
	Board(IDirect3DTexture9*);
	~Board();

	void Init();
	void Draw() const;

	Location __get_centerLoc() const;
};

#endif // __BOARD_H