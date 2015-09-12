#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <vector>
#include <d3d9.h>
#include "common.h"
#include "image.h"

using namespace std;

class Character{
private:
	int num;
	Location loc;
	IDirect3DTexture9** TexturePack;
	vector<Location> moveableList;
	int numMoveable;

public:
	Character();
	Character(int, Location, IDirect3DTexture9**);
	~Character();

	void Draw(Istat);
	void SearchMoveable();
	void Move();

	int get_num(){ return num; }
	Location get_loc(){ return loc; }
	IDirect3DTexture9* get_pSquareOverTexture(){ return TexturePack[sq_over]; }
	Location* get_moveableList(){ return &moveableList[0]; }
	int get_numMoveable(){ return numMoveable; }
};

#endif // __CHARACTER_H