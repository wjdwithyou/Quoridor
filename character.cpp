#include "character.h"
#include "dxfunc.h"
#include "board.h"

Character::Character(){}

Character::Character(IDirect3DTexture9* texture_, int x, int y)
	: pCharacterTexture(texture_)
{
	loc.x = x;
	loc.y = y;
}

Character::~Character(){}

void Character::Draw(Location board_loc){
	DrawTexture(pCharacterTexture, (float)CooToPxl(board_loc.x, loc.x), (float)CooToPxl(board_loc.y, loc.y), 1.0f, 0.0f);
}

int Character::CooToPxl(int point, int coo){
	return coo * 65 + point;			///// square 완성되면 수정할 것.
}