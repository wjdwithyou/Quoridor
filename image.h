#ifndef __IMAGE_H
#define __IMAGE_H

#include <d3d9.h>

enum Istat{ base, sq_over, clicked };

class Image{
private:
	const int MAX_ISTAT;

public:
	IDirect3DTexture9*** Character_Texture_Pack;

	IDirect3DTexture9* Background_Texture;
	IDirect3DTexture9* Board_Texture;
	IDirect3DTexture9* Square_Over_Texture;
	IDirect3DTexture9* Square_Moveable_Texture;

public:
	Image();
	~Image();

	void InitPack();
	void LoadTextures();
	void MakePack();
	void ReleaseTexture(IDirect3DTexture9*);
	void ReleaseTexture(IDirect3DTexture9***);
	void ReleaseTextures();
};

#endif // __IMAGE_H