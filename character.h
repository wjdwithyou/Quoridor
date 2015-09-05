#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <d3d9.h>

class Character{
private:
	int x;
	int y;
	IDirect3DTexture9* pCharacterTexture;
public:
	Character();
	Character(IDirect3DTexture9*, int, int);
	~Character();

	void Draw();
};

#endif // __CHARACTER_H