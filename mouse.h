#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"
#include "square.h"
#include "character.h"

enum Status{ ready, clk_chara, clk_bar };

class Mouse{
private:
	Status status;
	Location pxloc;	// int로 형 변환된 mxy-pixel이 들어온다 from callback
	Location locoo;	// (-1, a), (b, -1), ...
	//IDirect3DTexture9* texture_;

public:
	Mouse();
	~Mouse();

	Square* CheckOnSquare();
	Character* CheckOnCharacter();

	void __set_loc(int, int);
};

#endif // __MOUSE_H