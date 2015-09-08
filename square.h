#ifndef __SQUARE_H
#define __SQUARE_H

#include "character.h"

class Square{
private:
	Character* onthis;

public:
	Square();
	~Square();

	Character* get_onthis(){ return onthis; }
	void set_onthis(Character* c){ onthis = c; return; }
};

#endif // __SQUARE_H