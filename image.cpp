#include "image.h"
#include "dxfunc.h"

IDirect3DTexture9* Background_Texture;
IDirect3DTexture9* Board_Texture;
IDirect3DTexture9* Character_Black_Texture;
IDirect3DTexture9* Character_Brown_Texture;
IDirect3DTexture9* Square_Over_Texture;
IDirect3DTexture9* Square_Over_Black_Texture;
IDirect3DTexture9* Square_Over_Brown_Texture;

void LoadTextures(){
	LoadTexture("Image/background.png", &Background_Texture);
	LoadTexture("Image/board.png", &Board_Texture);
	LoadTexture("Image/character_black.png", &Character_Black_Texture);
	LoadTexture("Image/character_brown.png", &Character_Brown_Texture);
	LoadTexture("Image/square_over.png", &Square_Over_Texture);
	LoadTexture("Image/square_over_black.png", &Square_Over_Black_Texture);
	LoadTexture("Image/square_over_brown.png", &Square_Over_Brown_Texture);

	return;
}

void ReleaseTexture(IDirect3DTexture9* texture_){
	if (texture_ != NULL){
		texture_->Release();
		texture_ = NULL;
	}

	return;
}

void ReleaseTextures(){
	ReleaseTexture(Background_Texture);
	ReleaseTexture(Board_Texture);
	ReleaseTexture(Character_Black_Texture);
	ReleaseTexture(Character_Brown_Texture);
	ReleaseTexture(Square_Over_Texture);
	ReleaseTexture(Square_Over_Black_Texture);
	ReleaseTexture(Square_Over_Brown_Texture);

	return;
}