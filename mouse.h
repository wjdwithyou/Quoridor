#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"

class Mouse{
private:
	Location loc;
	//IDirect3DTexture9* texture_;

public:
	Mouse();
	~Mouse();

	Location CheckOnSquare(Location);

	Location get_loc(){ return loc; }
	void set_loc(int x, int y){ loc.x = x; loc.y = y; return; }
};

#endif // __MOUSE_H