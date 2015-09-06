#include "mouse.h"

Mouse::Mouse(){}
Mouse::~Mouse(){}

Location Mouse::CheckOnSquare(Location point){
	Location tmp;

	tmp.x = PxlToCoo(point.x, static_cast<float>(loc.x));
	tmp.y = PxlToCoo(point.y, static_cast<float>(loc.y));

	if (tmp.x != -1 && tmp.y != -1);
	else
		tmp.x = tmp.y = -1;

	return tmp;
}