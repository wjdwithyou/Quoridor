#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <d3d9.h>
#include "common.h"

class Character{
private:
	int num;
	Location loc;
	IDirect3DTexture9* pCharacterTexture;
	IDirect3DTexture9* pSquareOverTexture;

public:
	Character();
	Character(int, IDirect3DTexture9*, IDirect3DTexture9*, int, int);
	~Character();

	void Draw();

	Location get_loc(){ return loc; }
	//IDirect3DTexture9* get_pCharacterTexture(){ return pCharacterTexture; }
	IDirect3DTexture9* get_pSquareOverTexture(){ return pSquareOverTexture; }
};

#endif // __CHARACTER_H