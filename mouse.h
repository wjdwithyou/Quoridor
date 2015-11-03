#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"

class Button;
class Bar;
class Point;
class Player;

class Mouse{
protected:
	//Mstat status;
	Location pxloc;	// int�� �� ��ȯ�� mxy-pixel�� ���´� from callback

public:
	Mouse();
	~Mouse();

	virtual void Click(Player**);
	virtual void R_Click();
	virtual void Wheel(bool) const;

	Button* CheckOnButton() const;	// override?
	virtual Bar* CheckOnBar() const;
	virtual Point* CheckAroundPoint() const;

	virtual void __set_loc(int, int);	// override

	Location get_pxloc() const{ return pxloc; }
};

#endif // __MOUSE_H