#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"

class Button;
class Bar;
class Point;
class Player;

class Mouse{
protected:
	Location pxloc;	// int로 형 변환된 mxy-pixel이 들어온다 from callback

public:
	Mouse();
	~Mouse();

	virtual void Click(Player**);
	virtual void R_Click();
	virtual void Wheel(bool) const;

	Button* CheckOnButton() const;	// override?
	virtual Bar* CheckOnBar(Player*) const;
	virtual Point* CheckAroundPoint(Player*) const;

	virtual void __set_loc(int, int);

	Location get_pxloc() const{ return pxloc; }
};

#endif // __MOUSE_H