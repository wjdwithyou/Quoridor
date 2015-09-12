#include "mouse.h"
#include "board.h"
#include "square.h"
#include "player.h"

Mouse::Mouse()
	: status(ready)
{
	pxloc.x = pxloc.y = 0;
	locoo.x = locoo.y = -1;
}

Mouse::Mouse(Location loc)
	: status(clk_chara), locoo(loc)
{
	pxloc.x = pxloc.y = 0;	/////
}

Mouse::~Mouse(){}

void Mouse::Click(Player* turn){
	if (CheckOnCharacter() == turn->get_character()){
		status = clk_chara;

		turn->get_character()->SearchMoveable();

		//impl.
	}

	// TODO: if bar

	return;
}

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