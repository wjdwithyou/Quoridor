#ifndef __SQUARE_H
#define __SQUARE_H

#include "character.h"

class Square{
private:
	Location loc;
	Character* onthis;

public:
	Square();
	Square(int, int);
	~Square();

	Location get_loc(){ return loc; }
	Character* get_onthis(){ return onthis; }
	void set_onthis(Character* c){ onthis = c; return; }
};

#endif // __SQUARE_H