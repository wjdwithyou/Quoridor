#include "character.h"
#include "dxfunc.h"

Character::Character(){}

Character::Character(IDirect3DTexture9* texture_, int x, int y)
	: x(x), y(y), pCharacterTexture(texture_){

}

Character::~Character(){}

void Character::Draw(){
	DrawTexture(pCharacterTexture, 0, 0, 1.0f, 0.0f);
}