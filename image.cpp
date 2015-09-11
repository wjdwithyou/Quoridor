#include "image.h"
#include "dxfunc.h"
#include "player.h"

Image::Image()
	: MAX_ISTAT(3)
{
	InitPack();
}

Image::~Image(){}

void Image::InitPack(){
	int np = Player().get_numPlayer();

	Character_Texture_Pack = new IDirect3DTexture9**[np];

	for (int i = 0; i < np; ++i)
		Character_Texture_Pack[i] = new IDirect3DTexture9*[MAX_ISTAT];

	return;
}

void Image::LoadTextures(){
	LoadTexture("Image/background.png", &Background_Texture);
	LoadTexture("Image/board.png", &Board_Texture);
	LoadTexture("Image/square_over.png", &Square_Over_Texture);
	LoadTexture("Image/square_moveable.png", &Square_Moveable_Texture);

	// character1
	LoadTexture("Image/character1.png", &Character_Texture_Pack[0][base]);
	LoadTexture("Image/square_over_character1.png", &Character_Texture_Pack[0][sq_over]);
	LoadTexture("Image/clicked_character1.png", &Character_Texture_Pack[0][clicked]);

	// character2
	LoadTexture("Image/character2.png", &Character_Texture_Pack[1][base]);
	LoadTexture("Image/square_over_character2.png", &Character_Texture_Pack[1][sq_over]);
	LoadTexture("Image/clicked_character2.png", &Character_Texture_Pack[1][clicked]);

	return;
}

void Image::ReleaseTexture(IDirect3DTexture9* texture_){
	if (texture_ != NULL){
		texture_->Release();
		texture_ = NULL;
	}

	return;
}

void Image::ReleaseTexture(IDirect3DTexture9*** texturePack){
	for (int i = 0; i < Player().get_numPlayer(); ++i){
		for (int j = 0; j < MAX_ISTAT; ++j)
			ReleaseTexture(texturePack[i][j]);
	}

	return;
}

void Image::ReleaseTextures(){
	ReleaseTexture(Background_Texture);
	ReleaseTexture(Board_Texture);
	ReleaseTexture(Square_Over_Texture);
	ReleaseTexture(Square_Moveable_Texture);

	ReleaseTexture(Character_Texture_Pack);

	return;
}