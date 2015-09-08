#include "mouse.h"
#include "board.h"
#include "character.h"

Mouse::Mouse()
	: status(ready){

}

Mouse::~Mouse(){}

Location Mouse::CheckOnSquare(){	// checkOnSquare�� square�� �����ϰ� checkOnCharacter�� character�� ����?
	Location out = {-1, -1};			// ������ Location�� �� �� ������ (square���� �߰��ؾ���) 

	if (locoo.x == -1 || locoo.y == -1)
		return out;
	
	return locoo;
}

Location Mouse::CheckOnCharacter(){
	Location tmp = CheckOnSquare();
	Character* c = Board::board[tmp.y][tmp.x].get_onthis();

	if (tmp.x == -1)
		return tmp;

	if (c == NULL)
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