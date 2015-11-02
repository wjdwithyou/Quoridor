#include "menuProcess.h"
#include <cstdio>
#include "dxfunc.h"
#include "image.h"	// background
#include "mouse.h"
#include "menu.h"
#include "debug.h"

MenuProcess::MenuProcess()
	: Process(), mouse(new Mouse()), menu(new Menu()){

}

MenuProcess::~MenuProcess(){}

void MenuProcess::Init(int){
	// impl
	return;
}

void MenuProcess::Loop() const{
	sprintf_s(debug->sz_fps, "%02.2fFPS", debug->CalcFPS());

	sprintf_s(debug->sz_pxl_x, "pxl.x: %4d", mouse->get_pxloc().x);
	sprintf_s(debug->sz_pxl_y, "pxl.y: %4d", mouse->get_pxloc().y);

	sprintf_s(debug->sz_temp1, "%d %d", Menu::TITLE_LOC_X, Menu::TITLE_LOC_Y);
	

	if (Device){
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0);
	
		if (SUCCEEDED(Device->BeginScene())){
			Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			DrawTexture(image->Background_Texture, 0, 0, 1.0f, 0.0f);

			
			RECT rc = {0, 0, WindowWidth, WindowHeight};

			debug->PrintFPS(rc);
			debug->PrintValue(rc);
			

			menu->DrawTitle();
			menu->Draw();



			Sprite->End();
	
			Device->EndScene();
		}

		Device->Present(0, 0, 0, 0);
	}

	return;
}