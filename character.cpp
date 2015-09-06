#include "character.h"
#include "dxfunc.h"
#include "board.h"

Character::Character(){}

Character::Character(int n, IDirect3DTexture9* chara_texture, IDirect3DTexture9* square_over_texture, int x, int y)
	: num(n), pCharacterTexture(chara_texture), pSquareOverTexture(square_over_texture)
{
	loc.x = x;
	loc.y = y;
}

Character::~Character(){}

void Character::Draw(){
	DrawTexture(pCharacterTexture, CooToPxl(loc), 1.0f, 0.0f);
	return;
}