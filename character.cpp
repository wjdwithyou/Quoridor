#include "character.h"
#include "dxfunc.h"
#include "gamingMouse.h"
#include "board.h"
#include "square.h"
#include "point.h"

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
/*
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
*/

bool Character::Check() const{
	return Check(loc);
}

bool Character::Check(Location _loc) const{
	if (dest.y == -1){
		if (dest.x != _loc.x)
			return false;
	}
	else{
		if (dest.y != _loc.y)
			return false;
	}

	return true;
}

void Character::SearchMoveable(){
	// REARRNAGE
	bool pass;
	Location tmp[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	Location imp[4] = {{-1, -1}, {-1, 0}, {0, 0}, {0, -1}};
	Bdir dmp[2] = {d_vtc, d_hrz};

	for (int i = 0; i < 4; ++i){
		tmp[i].x += loc.x;
		tmp[i].y += loc.y;

		imp[i].x += loc.x;
		imp[i].y += loc.y;
	}
	
	for (int i = 0; i < 4; ++i){
		pass = false;

		if (!CheckCooRange(tmp[i], Board::SIZE))
			continue;

		// TODO: add condition about < my - enemy - wall > status

		for (int j = 0; j < 2; ++j){
			if (!CheckCooRange(imp[(i+j)%4], Board::SIZE - 1))
				continue;

			if (Board::its[imp[(i+j)%4].y][imp[(i+j)%4].x]->get_onBarStatus() == dmp[i%2]){
				pass = true;
				break;
			}
		}

		if (pass)
			continue;

		if (GamingMouse(tmp[i]).CheckOnCharacter() == NULL){
			moveableList.push_back(tmp[i]);
			++numMoveable;
		}
		else{
			Location iimp[2] = {imp[i], imp[(i+1)%4]};

			if (loc.y == tmp[i].y){
				tmp[i].x += (loc.x < tmp[i].x)? 1: -1;
				iimp[0].x += (loc.x < tmp[i].x)? 1: -1;
				iimp[1].x += (loc.x < tmp[i].x)? 1: -1;
			}
			else{
				tmp[i].y += (loc.y < tmp[i].y)? 1: -1;
				iimp[0].y += (loc.y < tmp[i].y)? 1: -1;
				iimp[1].y += (loc.y < tmp[i].y)? 1: -1;
			}
			
			if (CheckCooRange(tmp[i], Board::SIZE)){
				for (int j = 0; j < 2; ++j){
					if (!CheckCooRange(iimp[j], Board::SIZE - 1))
						continue;

					if (Board::its[iimp[j].y][iimp[j].x]->get_onBarStatus() == dmp[i%2]){
						pass = true;
						break;
					}
				}

				if (pass){
					// impl.
					continue;
				}

				if (GamingMouse(tmp[i]).CheckOnCharacter() == NULL){
					moveableList.push_back(tmp[i]);
					++numMoveable;
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
/*
bool Character::CheckReachable() const{
	for (int i = 0; i < Board::SIZE; ++i){
		for (int j = 0; j < Board::SIZE; ++j)
			Board::check[i][j] = false;
	}

	return CheckReachable(loc);
}
*/

bool Character::CheckReachable(Location m_its, Bdir d) const{
	bool tmp;

	for (int i = 0; i < Board::SIZE; ++i){
		for (int j = 0; j < Board::SIZE; ++j)
			Board::check[i][j] = false;
	}

	Board::its[m_its.y][m_its.x]->set_onBarStatus(d);

	tmp = CheckReachable(loc);

	Board::its[m_its.y][m_its.x]->set_onBarStatus(d_none);

	return tmp;
}

bool Character::CheckReachable(Location c_loc) const{	// recursive?
	bool pass;
	Location tmp[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	Location imp[4] = {{-1, -1}, {-1, 0}, {0, 0}, {0, -1}};
	Bdir dmp[2] = {d_vtc, d_hrz};

	if (Check(c_loc))
		return true;

	for (int i = 0; i < 4; ++i){
		tmp[i].x += c_loc.x;
		tmp[i].y += c_loc.y;

		imp[i].x += c_loc.x;
		imp[i].y += c_loc.y;
	}

	for (int i = 0; i < 4; ++i){
		pass = false;

		if (!CheckCooRange(tmp[i], Board::SIZE))
			continue;

		if (Board::check[tmp[i].y][tmp[i].x] == true)
			continue;

		for (int j = 0; j < 2; ++j){
			if (!CheckCooRange(imp[(i+j)%4], Board::SIZE - 1))
				continue;

			if (Board::its[imp[(i+j)%4].y][imp[(i+j)%4].x]->get_onBarStatus() == dmp[i%2]){
				pass = true;
				break;
			}
		}

		if (pass)
			continue;

		Board::check[c_loc.y][c_loc.x] = true;

		if (CheckReachable(tmp[i]))
			return true;
	}

	return false;
}
/*
bool Character::CheckWall(Location imp1, Location imp2, Bdir d) const{		// 벽 하나에 대해서 check
	if (Board::its[imp1.y][imp1.x]->get_onBarStatus() == d)
		return true;
	else if (Board::its[imp2.y][imp2.x]->get_onBarStatus() == d)
		return true;
	else
		return false;
}
*/