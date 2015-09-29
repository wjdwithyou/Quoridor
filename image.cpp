#include "image.h"
#include "dxfunc.h"
#include "square.h"
#include "player.h"
#include "bar.h"

#define NUM_BAR_IMAGE 3		// temp

Image::Image(){
	InitPack();
}

Image::~Image(){}

void Image::InitPack(){
	Square_Texture_Pack = new IDirect3DTexture9*[Square::MAX_QSTAT];
	Character_Texture_Pack = new IDirect3DTexture9*[Player().get_numPlayer()];
	Bar_Texture_Pack = new IDirect3DTexture9*[NUM_BAR_IMAGE];

	return;
}

void Image::LoadTextures(){
	LoadTexture("Image/background.png", &Background_Texture);
	LoadTexture("Image/board.png", &Board_Texture);
	LoadTexture("Image/effect.png", &Effect_Texture);

	// TODO: auto numbering
	LoadTexture("Image/square_base.png", &Square_Texture_Pack[q_base]);
	LoadTexture("Image/square_clicked.png", &Square_Texture_Pack[q_clicked]);
	LoadTexture("Image/square_moveable.png", &Square_Texture_Pack[q_moveable]);
	LoadTexture("Image/square_win.png", &Square_Texture_Pack[q_win]);

	LoadTexture("Image/character1.png", &Character_Texture_Pack[0]);
	LoadTexture("Image/character2.png", &Character_Texture_Pack[1]);
	LoadTexture("Image/character1.png", &Character_Texture_Pack[2]);	// temp
	LoadTexture("Image/character2.png", &Character_Texture_Pack[3]);	// temp

	LoadTexture("Image/bar.png", &Bar_Texture_Pack[b_over]);
	LoadTexture("Image/bar_onmouse.png", &Bar_Texture_Pack[b_on]);
	LoadTexture("Image/bar.png", &Bar_Texture_Pack[b_clicked]);		// temp

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

	ReleaseTexture(Square_Texture_Pack, Square::MAX_QSTAT);
	ReleaseTexture(Character_Texture_Pack, Player().get_numPlayer());
	ReleaseTexture(Bar_Texture_Pack, NUM_BAR_IMAGE);	// temp

	return;
}