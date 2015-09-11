#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <d3d9.h>
#include "common.h"

class Character{
private:
	int num;
	Location loc;
	IDirect3DTexture9** TexturePack;

public:
	Character();
	Character(int, IDirect3DTexture9**, Location);
	~Character();

	void Draw();

	int get_num(){ return num; }
	Location get_loc(){ return loc; }
	IDirect3DTexture9* get_pSquareOverTexture(){ return TexturePack[sq_over]; }
};

#endif // __CHARACTER_H