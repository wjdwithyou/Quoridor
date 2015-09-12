#include "character.h"
#include "dxfunc.h"
#include "mouse.h"
#include "board.h"
#include "square.h"

Character::Character(){}

Character::Character(int n, Location loc, IDirect3DTexture9** texturePack)
	: num(n), loc(loc), TexturePack(texturePack), numMoveable(0)
{
	Board::board[loc.y][loc.x]->set_onthis(this);
}

Character::~Character(){}

void Character::Draw(Istat stat){
	DrawTexture(TexturePack[stat], CooToPxl(loc), 1.0f, 0.0f);
	return;
}

void Character::SearchMoveable(){
	Location tmp[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
	
	for (int i = 0; i < 4; ++i){
		tmp[i].x += loc.x;
		tmp[i].y += loc.y;

		if (CheckCooRange(tmp[i])){
			// TODO: add condition about bar
			// TODO: add condition about continuous character in asle

			if (Mouse(tmp[i]).CheckOnCharacter() == NULL){
				moveableList.push_back(tmp[i]);
				++numMoveable;
				// impl.
			}
			else{
				if (loc.y == tmp[i].y)
					tmp[i].x += (loc.x < tmp[i].x)? 1: -1;
				else
					tmp[i].y += (loc.y < tmp[i].y)? 1: -1;

				if (CheckCooRange(tmp[i])){
					if (Mouse(tmp[i]).CheckOnCharacter() == NULL){
						moveableList.push_back(tmp[i]);
						++numMoveable;
					}
					else{
						//impl.
					}
				}
			}
		}
	}

	return;
}

void Character::Move(){

	return;
}