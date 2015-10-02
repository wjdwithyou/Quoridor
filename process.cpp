#include "process.h"
#include <stdio.h>
#include "dxfunc.h"
#include "image.h"
#include "mouse.h"
#include "common.h"
#include "menu.h"
#include "board.h"
#include "player.h"
#include "character.h"
#include "bar.h"
#include "debug.h"

#include "button.h"	/////

Process::Process(){}

Process::Process(WNDCLASS WndClass)
	: menu(new Menu()), _board(new Board(image->Board_Texture)), playerList(NULL)
{
	hWnd = CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, NULL, NULL, WindowWidth + 6, WindowHeight + 32, NULL, NULL, WndClass.hInstance, NULL);
	
	/*
	if (!hWnd){
		MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}
	*/
	
	InitializeDevice();

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	image->LoadTextures();

	Player().InitPlayer(&playerList);
}

Process::~Process(){}

Pstat Process::status = p_menu;

void Process::MenuLoop() const{
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
			//debug->PrintValue(rc);
			

			menu->DrawTitle();
			menu->Draw();



			Sprite->End();
	
			Device->EndScene();
		}

		Device->Present(0, 0, 0, 0);
	}

	return;
}

void Process::GameLoop() const{
	///////////////////////////////////////////
	// convert for debug
	sprintf_s(debug->sz_fps, "%02.2fFPS", debug->CalcFPS()); // 프레임을 문자열로 만들어서 sz_fps에 저장

	sprintf_s(debug->sz_cturn, "%d player", turn->get_character()->get_num() + 1);
	sprintf_s(debug->sz_pxl_x, "pxl.x: %4d", mouse->get_pxloc().x);
	sprintf_s(debug->sz_pxl_y, "pxl.y: %4d", mouse->get_pxloc().y);
	sprintf_s(debug->sz_loc_x, "loc.x: %4d", mouse->get_locoo().x);
	sprintf_s(debug->sz_loc_y, "loc.y: %4d", mouse->get_locoo().y);
	sprintf_s(debug->sz_locits_x, "its.x: %4d", mouse->get_locooits().x);
	sprintf_s(debug->sz_locits_y, "its.y: %4d", mouse->get_locooits().y);
	sprintf_s(debug->sz_mstat, "mstat: %4d", mouse->get_status());

	if (mouse->get_locooits().x != -1 && mouse->get_locooits().y != -1){
		if (mouse->get_pick() != NULL)
			sprintf_s(debug->sz_temp1, "%d", mouse->CheckAroundUsedBar());
		else
			sprintf_s(debug->sz_temp1, "%s", "FREE");
	}
	//sprintf_s(debug->sz_temp2, "%d", _board->its[3][3]->get_onBarStatus());
	//sprintf_s(debug->sz_temp2, "%d", turn->get_barList()[0]->get_loc().y);

	// convert end
	///////////////////////////////////////////



	//KeyInput(); // 여기서 먼저 키입력을 받고
	//GameLoop(); // 프레임당 처리는 여기서 한다.

	if (Device){
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0);
	
		if (SUCCEEDED(Device->BeginScene())){
			Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			// texture, x, y, size, angle
			DrawTexture(image->Background_Texture, 0, 0, 1.0f, 0.0f); // background


				

				

			// 텍스트가 그려질 사각형의 좌표를 넣는다.
			// left, top, right, bottom
			// {0, 0, 0, 0}의 기준 : 가장 최근에 draw한 그림
				
			RECT rc = {0, 0, WindowWidth, WindowHeight};

			debug->PrintFPS(rc);
			//debug->PrintValue(rc);

			//여기서 폰트를 출력한다.
			//첫번째인자: 스프라이트 디바이스를 넣는곳. NULL을 넣어도 출력은 되긴 되더라
			//두번째인자: 문자열을 넣는곳
			//세번째인자: 출력할 문자열 내의 문자의 수. NULL로 끝나는 문자열은 -1을 넣으면 된다.
			//네번째인자: 텍스트의 포맷을 설정한다. 여기선 왼쪽정렬, 한줄만그리기, 잘리지않기 옵션임. 자세한 설명은 클럽에 올림
			//다섯번째인자: 텍스트 컬러
				
			_board->Draw();		// square

			mouse->DrawEffect();	// mouse

			for (int i = 0; i < Player().get_numPlayer(); ++i)		// character
				playerList[i]->get_character()->Draw();



			///// bar draw test /////
			// TODO: rearrange dirty codes :(

			for (int i = 0; i < Player().get_numPlayer(); ++i){		// bar
				for (int j = 0; j < playerList[i]->get_maxBar(); ++j){		// 전부 그려야하기 때문에 numBar가 아닌 maxBar
					if (playerList[i]->get_barList()[j] != mouse->get_pick())
						playerList[i]->get_barList()[j]->Draw();
				}
			}

			if (mouse->get_pick() != NULL)		// bar(picked)
				mouse->get_pick()->Draw();

			///// bar draw test end /////

			if (mouse->get_status() == m_etc)
				if (ending < 256){
					DrawEnding(image->Gameover_Texture, 0, 0, 1.0f, 0.0f);
					++ending;
				}
				else
					DrawTexture(image->Gameover_Texture, 0, 0, 1.0f, 0.0f);


			Sprite->End();
	
			Device->EndScene();
		}

		Device->Present(0, 0, 0, 0);
	}

	return;
}