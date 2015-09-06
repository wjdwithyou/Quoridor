#include "mouse.h"

Mouse::Mouse(){}
Mouse::~Mouse(){}

Location Mouse::CheckOnSquare(){
	Location tmp = PxlToCoo(pxloc);

	if (tmp.x == -1 || tmp.y == -1)
		tmp.x = tmp.y = -1;

	return tmp;
}
/*
Location Mouse::CheckOnCharacter(Location point, Location chara_loc){
	Location tmp;

	tmp.x = PxlToCoo(point.x, static_cast<float>(pxloc.x));
	tmp.y = PxlToCoo(point.y, static_cast<float>(pxloc.y));

	// impl.

	return tmp;
}
*/
void Mouse::__set_loc(int x, int y){
	pxloc.x = x;
	pxloc.y = y;

	locoo = PxlToCoo(pxloc);

	return;
}