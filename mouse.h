#ifndef __MOUSE_H
#define __MOUSE_H

#include "common.h"

class Button;
class Bar;
class Point;

class Mouse{
protected:
	//Mstat status;
	Location pxloc;	// int로 형 변환된 mxy-pixel이 들어온다 from callback

public:
	Mouse();
	~Mouse();

	void Click();	// override
	virtual void R_Click();
	virtual void Wheel(bool) const;

	Button* CheckOnButton() const;	// override?
	virtual Bar* CheckOnBar() const;
	virtual Point* CheckAroundPoint() const;

	void __set_loc(int, int);	// override

	Location get_pxloc() const{ return pxloc; }
};

#endif // __MOUSE_H