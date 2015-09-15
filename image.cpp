#include "image.h"
#include "dxfunc.h"
#include "square.h"
#include "player.h"

Image::Image()
	: MAX_ISTAT(3)
{
	InitPack();
}

Image::~Image(){}

void Image::InitPack(){
	int np = Player().get_numPlayer();

	Square_Texture = new IDirect3DTexture9*[Square::MAX_QSTAT];
	Character_Texture = new IDirect3DTexture9*[np];

	return;
}

void Image::LoadTextures(){
	LoadTexture("Image/background.png", &Background_Texture);
	LoadTexture("Image/board.png", &Board_Texture);
	LoadTexture("Image/effect.png", &Effect_Texture);

	LoadTexture("Image/square_base.png", &Square_Texture[q_base]);
	LoadTexture("Image/square_clicked.png", &Square_Texture[q_clicked]);
	LoadTexture("Image/square_moveable.png", &Square_Texture[q_moveable]);

	LoadTexture("Image/character1.png", &Character_Texture[0]);
	LoadTexture("Image/character2.png", &Character_Texture[1]);


	/*
	// character1
	LoadTexture("Image/character1.png", &Character_Texture_Pack[0][base]);
	LoadTexture("Image/square_over_character1.png", &Character_Texture_Pack[0][sq_over]);
	LoadTexture("Image/clicked_character1.png", &Character_Texture_Pack[0][clicked]);

	// character2
	LoadTexture("Image/character2.png", &Character_Texture_Pack[1][base]);
	LoadTexture("Image/square_over_character2.png", &Character_Texture_Pack[1][sq_over]);
	LoadTexture("Image/clicked_character2.png", &Character_Texture_Pack[1][clicked]);
	*/

	return;
}

void Image::ReleaseTexture(IDirect3DTexture9* texture_){
	if (texture_ != NULL){
		texture_->Release();
		texture_ = NULL;
	}

	return;
}

void Image::ReleaseTexture(IDirect3DTexture9** texture_, int n){
	for (int i = 0; i < n; ++i)
		ReleaseTexture(texture_[i]);

	return;
}

void Image::ReleaseTextures(){
	ReleaseTexture(Background_Texture);
	ReleaseTexture(Board_Texture);
	ReleaseTexture(Effect_Texture);

	ReleaseTexture(Square_Texture, Square::MAX_QSTAT);
	ReleaseTexture(Character_Texture, Player().get_numPlayer());

	return;
}