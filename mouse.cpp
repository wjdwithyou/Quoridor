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
	Character* cmp = turn->get_character();

	switch (status){
	case base:
		if (cmp == CheckOnCharacter()){
			status = clk_chara;

			cmp->SearchMoveable();

			//impl.
		}

		break;
	case clk_chara:
		// TODO: for Location, need operator overloading (==)

		for (int i = 0; i < cmp->get_numMoveable(); ++i){
			if (locoo.x == cmp->get_moveableList()[i].x &&
				locoo.y == cmp->get_moveableList()[i].y){
					cmp->Move(cmp->get_moveableList()[i]);
					
					// impl.

					break;
			}
		}

		break;

	case clk_bar:
		break;

	default:
		break;
	}

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