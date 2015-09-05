#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <d3d9.h>
#include "common.h"

class Character{
private:
	Location loc;
	IDirect3DTexture9* pCharacterTexture;

public:
	Character();
	Character(IDirect3DTexture9*, int, int);
	~Character();

	void Draw(Location);

	int CooToPxl(int, int);
};

#endif // __CHARACTER_H