#include "mouse.h"
#include "board.h"

Mouse::Mouse()
	: status(ready)
{
	pxloc.x = pxloc.y = 0;
	locoo.x = locoo.y = -1;
}

Mouse::~Mouse(){}

Square* Mouse::CheckOnSquare(){
	if (locoo.x == -1 || locoo.y == -1)
		return NULL;

	return Board::board[locoo.y][locoo.x];
}

Character* Mouse::CheckOnCharacter(){
	if (CheckOnSquare() == NULL)
		return NULL;

	return CheckOnSquare()->get_onthis();
}

void Mouse::__set_loc(int x, int y){
	pxloc.x = x;
	pxloc.y = y;

	locoo = PxlToCoo(pxloc);

	return;
}