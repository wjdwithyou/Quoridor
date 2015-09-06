#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"

class Mouse{
private:
	Location pxloc;	// int로 형 변환된 mxy-pixel이 들어온다 from callback
	Location locoo;
	//IDirect3DTexture9* texture_;

public:
	Mouse();
	~Mouse();

	Location CheckOnSquare();
	//Location CheckOnCharacter(Location, Location);

	Location get_loc(){ return pxloc; }
	void __set_loc(int, int);
};

#endif // __MOUSE_H