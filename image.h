#ifndef __IMAGE_H
#define __IMAGE_H

#include <d3d9.h>

extern IDirect3DTexture9* Background_Texture;
extern IDirect3DTexture9* Board_Texture;
extern IDirect3DTexture9* Character_Black_Texture;
extern IDirect3DTexture9* Character_Brown_Texture;

void ReleaseTexture();

#endif // __IMAGE_H