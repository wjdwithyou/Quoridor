#include "character.h"
#include "dxfunc.h"
#include "board.h"

Character::Character(){}

Character::Character(int n, IDirect3DTexture9** texturePack, Location loc)
	: num(n), TexturePack(texturePack), loc(loc)
{
	Board::board[loc.y][loc.x]->set_onthis(this);
}

Character::~Character(){}

void Character::Draw(){
	DrawTexture(TexturePack[base], CooToPxl(loc), 1.0f, 0.0f);
	return;
}