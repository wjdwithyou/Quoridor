#include "gameProcess.h"
#include <cstdio>
#include "dxfunc.h"
#include "common.h"
#include "image.h"
#include "gamingMouse.h"
#include "board.h"
#include "player.h"
#include "character.h"
#include "bar.h"
#include "debug.h"

GameProcess::GameProcess()
	: Process(new GamingMouse()), /*mouse(new GamingMouse()), */gamingMouse(dynamic_cast<GamingMouse*>(mouse)), _board(new Board(image->Board_Texture)), playerList(NULL), turn(NULL)
{
	g_turn = &turn;
}

GameProcess::~GameProcess(){}

/*
void GameProcess::Init(int n){
	Player().InitPlayer(&playerList, &turn);
	return;
}
*/

void GameProcess::Init(){
	Player().InitPlayer(&playerList, &turn);
	return;
}

void GameProcess::Loop() const{
	///////////////////////////////////////////
	// convert for debug
	sprintf_s(debug->sz_fps, "%02.2fFPS", debug->CalcFPS()); // �������� ���ڿ��� ���� sz_fps�� ����

	sprintf_s(debug->sz_cturn, "%d player", turn->get_character()->get_num() + 1);
	sprintf_s(debug->sz_pxl_x, "pxl.x: %4d", gamingMouse->get_pxloc().x);
	sprintf_s(debug->sz_pxl_y, "pxl.y: %4d", gamingMouse->get_pxloc().y);
	sprintf_s(debug->sz_loc_x, "loc.x: %4d", gamingMouse->get_locoo().x);
	sprintf_s(debug->sz_loc_y, "loc.y: %4d", gamingMouse->get_locoo().y);
	sprintf_s(debug->sz_locits_x, "its.x: %4d", gamingMouse->get_locooits().x);
	sprintf_s(debug->sz_locits_y, "its.y: %4d", gamingMouse->get_locooits().y);
	sprintf_s(debug->sz_mstat, "mstat: %4d", gamingMouse->get_status());

	if (gamingMouse->get_locooits().x != -1 && gamingMouse->get_locooits().y != -1){
		if (gamingMouse->get_pick() != NULL)
			sprintf_s(debug->sz_temp1, "%d", gamingMouse->CheckAroundUsedBar());
		else
			sprintf_s(debug->sz_temp1, "%s", "FREE");
	}
	//sprintf_s(debug->sz_temp2, "%d", _board->its[3][3]->get_onBarStatus());
	//sprintf_s(debug->sz_temp2, "%d", turn->get_barList()[0]->get_loc().y);

	// convert end
	///////////////////////////////////////////



	//KeyInput(); // ���⼭ ���� Ű�Է��� �ް�
	//GameLoop(); // �����Ӵ� ó���� ���⼭ �Ѵ�.

	if (Device){
		Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0);
	
		if (SUCCEEDED(Device->BeginScene())){
			Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			// texture, x, y, size, angle
			DrawTexture(image->Background_Texture, 0, 0, 1.0f, 0.0f); // background


				

				

			// �ؽ�Ʈ�� �׷��� �簢���� ��ǥ�� �ִ´�.
			// left, top, right, bottom
			// {0, 0, 0, 0}�� ���� : ���� �ֱٿ� draw�� �׸�
				
			RECT rc = {0, 0, WindowWidth, WindowHeight};

			debug->PrintFPS(rc);
			debug->PrintValue(rc);

			//���⼭ ��Ʈ�� ����Ѵ�.
			//ù��°����: ��������Ʈ ����̽��� �ִ°�. NULL�� �־ ����� �Ǳ� �Ǵ���
			//�ι�°����: ���ڿ��� �ִ°�
			//����°����: ����� ���ڿ� ���� ������ ��. NULL�� ������ ���ڿ��� -1�� ������ �ȴ�.
			//�׹�°����: �ؽ�Ʈ�� ������ �����Ѵ�. ���⼱ ��������, ���ٸ��׸���, �߸����ʱ� �ɼ���. �ڼ��� ������ Ŭ���� �ø�
			//�ټ���°����: �ؽ�Ʈ �÷�
				
			_board->Draw();		// square

			gamingMouse->DrawEffect();	// mouse

			for (int i = 0; i < Player().get_numPlayer(); ++i)		// character
				playerList[i]->get_character()->Draw();



			///// bar draw test /////
			// TODO: rearrange dirty codes :(

			for (int i = 0; i < Player().get_numPlayer(); ++i){		// bar
				for (int j = 0; j < playerList[i]->get_maxBar(); ++j){		// ���� �׷����ϱ� ������ numBar�� �ƴ� maxBar
					if (playerList[i]->get_barList()[j] != gamingMouse->get_pick())
						playerList[i]->get_barList()[j]->Draw(gamingMouse);
				}
			}

			if (gamingMouse->get_pick() != NULL)		// bar(picked)
				gamingMouse->get_pick()->Draw(gamingMouse);

			///// bar draw test end /////

			if (gamingMouse->get_status() == m_etc)
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