#include "image.h"
#include "dxfunc.h"
#include "button.h"
#include "square.h"
#include "player.h"
#include "bar.h"

#define NUM_BAR_IMAGE 6		// temp

Image::Image(){
	InitPack();
}

Image::~Image(){}

void Image::InitPack(){
	Button_Texture_Pack = new IDirect3DTexture9**[Button::NUM];

	for (int i = 0; i < Button::NUM; ++i)
		Button_Texture_Pack[i] = new IDirect3DTexture9*[Button::NUM_STAT];

	Square_Texture_Pack = new IDirect3DTexture9*[Square::MAX_QSTAT];
	Character_Texture_Pack = new IDirect3DTexture9*[Player().get_numPlayer()];
	Bar_Texture_Pack = new IDirect3DTexture9*[NUM_BAR_IMAGE];

	return;
}

void Image::LoadTextures(){
	LoadTexture("Image/title.png", &Title_Texture);
	LoadTexture("Image/background4.png", &Background_Texture);
	LoadTexture("Image/board.png", &Board_Texture);
	LoadTexture("Image/effect.png", &Effect_Texture);
	LoadTexture("Image/gameover.png", &Gameover_Texture);

	// TODO: auto numbering
	LoadTexture("Image/menu1.png", &Button_Texture_Pack[0][btn_down]);
	LoadTexture("Image/menu1_onmouse.png", &Button_Texture_Pack[0][btn_up]);
	LoadTexture("Image/menu2.png", &Button_Texture_Pack[1][btn_down]);
	LoadTexture("Image/menu2_onmouse.png", &Button_Texture_Pack[1][btn_up]);
	LoadTexture("Image/menu3.png", &Button_Texture_Pack[2][btn_down]);
	LoadTexture("Image/menu3_onmouse.png", &Button_Texture_Pack[2][btn_up]);
	LoadTexture("Image/menu4.png", &Button_Texture_Pack[3][btn_down]);
	LoadTexture("Image/menu4_onmouse.png", &Button_Texture_Pack[3][btn_up]);
	LoadTexture("Image/menu5.png", &Button_Texture_Pack[4][btn_down]);
	LoadTexture("Image/menu5_onmouse.png", &Button_Texture_Pack[4][btn_up]);

	LoadTexture("Image/square_base4.png", &Square_Texture_Pack[q_base]);
	LoadTexture("Image/square_clicked.png", &Square_Texture_Pack[q_clicked]);
	LoadTexture("Image/square_moveable.png", &Square_Texture_Pack[q_moveable]);
	LoadTexture("Image/square_win.png", &Square_Texture_Pack[q_win]);

	LoadTexture("Image/character1.png", &Character_Texture_Pack[0]);
	LoadTexture("Image/character2.png", &Character_Texture_Pack[1]);
	LoadTexture("Image/character3.png", &Character_Texture_Pack[2]);	// temp
	LoadTexture("Image/character4.png", &Character_Texture_Pack[3]);	// temp

	LoadTexture("Image/bar.png", &Bar_Texture_Pack[b_over]);
	LoadTexture("Image/bar_onmouse.png", &Bar_Texture_Pack[b_on]);
	LoadTexture("Image/bar.png", &Bar_Texture_Pack[b_clicked]);		// temp
	LoadTexture("Image/bar_can.png", &Bar_Texture_Pack[b_can]);
	LoadTexture("Image/bar_cannot.png", &Bar_Texture_Pack[b_cannot]);
	LoadTexture("Image/bar_used.png", &Bar_Texture_Pack[b_used]);

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

void Image::ReleaseTexture(IDirect3DTexture9*** texture_, int a, int b){
	for (int i = 0; i < a; ++i)
		ReleaseTexture(texture_[i], b);

	return;
}

void Image::ReleaseTextures(){
	ReleaseTexture(Title_Texture);
	ReleaseTexture(Background_Texture);
	ReleaseTexture(Board_Texture);
	ReleaseTexture(Effect_Texture);
	ReleaseTexture(Gameover_Texture);

	ReleaseTexture(Button_Texture_Pack, Button::NUM, Button::NUM_STAT);
	ReleaseTexture(Square_Texture_Pack, Square::MAX_QSTAT);
	ReleaseTexture(Character_Texture_Pack, Player().get_numPlayer());
	ReleaseTexture(Bar_Texture_Pack, NUM_BAR_IMAGE);	// temp

	return;
}