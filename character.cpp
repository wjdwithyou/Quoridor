#include "character.h"
#include "dxfunc.h"
#include "mouse.h"
#include "board.h"
#include "square.h"

Character::Character()
	: dest(){

}

Character::Character(int n, Location dloc, Location sloc, IDirect3DTexture9* texture_)
	: dest(dloc), num(n), loc(sloc), texture_(texture_), numMoveable(0)
{
	Board::board[loc.y][loc.x]->set_onthis(this);
}

Character::~Character(){}

void Character::Draw() const{
	DrawTexture(texture_, CooToPxl(loc, Board::SIZE), 1.0f, 0.0f);
	return;
}

void Character::Move(Square* square){
	Board::board[loc.y][loc.x]->set_onthis(NULL);

	loc = square->get_loc();

	square->set_onthis(this);

	return;
}

bool Character::Check() const{
	if (dest.y == -1){
		if (dest.x != loc.x)
			return false;
	}
	else{
		if (dest.y != loc.y)
			return false;
	}

	return true;
}

void Character::SearchMoveable(){
	Location tmp[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
	
	for (int i = 0; i < 4; ++i){
		tmp[i].x += loc.x;
		tmp[i].y += loc.y;

		if (CheckCooRange(tmp[i], Board::SIZE)){
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

				if (CheckCooRange(tmp[i], Board::SIZE)){
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

void Character::RevealMoveable() const{
	for (int i = 0; i < numMoveable; ++i)
		Board::board[moveableList[i].y][moveableList[i].x]->set_status(q_moveable);

	return;
}

void Character::HideMoveable() const{
	for (int i = 0; i < numMoveable; ++i)
		Board::board[moveableList[i].y][moveableList[i].x]->set_status(q_base);

	return;
}

void Character::ResetMoveable(){
	for (int i = 0; i < numMoveable; ++i)
		moveableList.pop_back();

	numMoveable = 0;

	return;
}