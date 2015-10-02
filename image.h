#ifndef __IMAGE_H
#define __IMAGE_H

#include <d3d9.h>

class Image{
public:
	IDirect3DTexture9* Title_Texture;
	IDirect3DTexture9* Background_Texture;
	IDirect3DTexture9* Board_Texture;
	IDirect3DTexture9* Effect_Texture;
	IDirect3DTexture9* Gameover_Texture;

	IDirect3DTexture9*** Button_Texture_Pack;
	IDirect3DTexture9** Square_Texture_Pack;
	IDirect3DTexture9** Character_Texture_Pack;
	IDirect3DTexture9** Bar_Texture_Pack;

public:
	Image();
	~Image();

	void InitPack();
	void LoadTextures();
	void MakePack();
	void ReleaseTexture(IDirect3DTexture9*);
	void ReleaseTexture(IDirect3DTexture9**, int);
	void ReleaseTexture(IDirect3DTexture9***, int, int);
	void ReleaseTextures();
};

#endif // __IMAGE_H