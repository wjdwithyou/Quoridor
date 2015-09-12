#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"

class Square;
class Player;
class Character;

enum Mstat{ ready, clk_chara, clk_bar };

class Mouse{
private:
	Mstat status;
	Location pxloc;	// int로 형 변환된 mxy-pixel이 들어온다 from callback
	Location locoo;	// (-1, a), (b, -1), ...
	//IDirect3DTexture9* texture_;

public:
	Mouse();
	Mouse(Location);	/////
	~Mouse();

	void Click(Player*);
	Square* CheckOnSquare();
	Character* CheckOnCharacter();

	void __set_loc(int, int);

	Mstat get_status(){ return status; }
	
	// for test
	Location get_pxloc(){ return pxloc; }
	Location get_locoo(){ return locoo; }
	//

	void set_status(Mstat stat){ status = stat; return; }
};

#endif // __MOUSE_H