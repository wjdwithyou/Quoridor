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

	static Location loc;	// �ػ󵵿� ���� ����� �� ������ const X
	static Location itsloc;	// �ػ󵵿� ���� ����� �� ������ const X

	static Square*** board;
	static Point*** its;
	static bool** check;

public:
	Board();
	Board(IDirect3DTexture9*);
	~Board();

	void Init();
	void Draw() const;

	Location __get_centerLoc() const;
};

#endif // __BOARD_H