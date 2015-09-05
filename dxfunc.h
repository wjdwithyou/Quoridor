#ifndef __DXFUNC_H
#define __DXFUNC_H

#include <d3d9.h>
#include <d3dx9.h>

extern IDirect3DDevice9* Device;
extern ID3DXSprite* Sprite;
extern ID3DXFont* Font;

extern D3DXCOLOR Color; 
extern D3DXMATRIX World;
extern D3DXMATRIX Translation;
extern D3DXMATRIX Rotation;
extern D3DXMATRIX Scaling;

void InitializeDevice();
void LoadTexture(char*, IDirect3DTexture9**);
void DrawTexture(IDirect3DTexture9*, float, float, float, float);
void DrawC(IDirect3DTexture9*, float, float, float, float, float);

#endif // __DXFUNC_H