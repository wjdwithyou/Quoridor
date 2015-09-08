#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"

class Mouse{
private:
	Location pxloc;	// int�� �� ��ȯ�� mxy-pixel�� ���´� from callback
	Location locoo;	// (-1, a), (b, -1), ...
	//IDirect3DTexture9* texture_;

public:
	Mouse();
	~Mouse();

	Location CheckOnSquare();
	//Location CheckOnCharacter(Location, Location);

	void __set_loc(int, int);
};

#endif // __MOUSE_H