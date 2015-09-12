#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "api.h"
#include "dxfunc.h"
#include "mouse.h"
#include "board.h"
#include "square.h"
#include "player.h"
#include "debug.h"

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "winmm")
#pragma comment (lib, "dxguid")
#pragma comment (lib, "dinput8")

//void KeyInput();
void GameLoop();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow){
	WNDCLASS WndClass;
	
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = "Quoridor";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	srand((unsigned)time(NULL));
	
	if (!RegisterClass(&WndClass)){
		MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
	
	hWnd = CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, NULL, NULL, WindowWidth + 6, WindowHeight + 32, NULL, NULL, WndClass.hInstance, NULL);
	
	if (!hWnd){
		MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}
	
	InitializeDevice();

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	// 게임의 텍스쳐 로딩
	image->LoadTextures();

	Board* _board = new Board(image->Board_Texture);

	Player** playerList;
	//Player* turn;

	Player().InitPlayer(&playerList, &turn);

	while (Message.message != WM_QUIT){
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}



		///////////////////////////////////////////
		// convert for debug
		sprintf_s(debug->sz_fps, "%02.2fFPS", debug->CalcFPS()); // 프레임을 문자열로 만들어서 sz_fps에 저장

		sprintf_s(debug->sz_cturn, "%d player", turn->get_character()->get_num() + 1);
		sprintf_s(debug->sz_pxl_x, "pxl.x: %4d", mouse->get_pxloc().x);
		sprintf_s(debug->sz_pxl_y, "pxl.y: %4d", mouse->get_pxloc().y);
		sprintf_s(debug->sz_loc_x, "loc.x: %4d", mouse->get_locoo().x);
		sprintf_s(debug->sz_loc_y, "loc.y: %4d", mouse->get_locoo().y);
		sprintf_s(debug->sz_mstat, "mstat: %4d", mouse->get_status());

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
				debug->PrintValue(rc);

				//여기서 폰트를 출력한다.
				//첫번째인자: 스프라이트 디바이스를 넣는곳. NULL을 넣어도 출력은 되긴 되더라
				//두번째인자: 문자열을 넣는곳
				//세번째인자: 출력할 문자열 내의 문자의 수. NULL로 끝나는 문자열은 -1을 넣으면 된다.
				//네번째인자: 텍스트의 포맷을 설정한다. 여기선 왼쪽정렬, 한줄만그리기, 잘리지않기 옵션임. 자세한 설명은 클럽에 올림
				//다섯번째인자: 텍스트 컬러



				_board->Draw();

				for (int i = 0; i < Player().get_numPlayer(); ++i)
					playerList[i]->get_character()->Draw(base);

				if (mouse->CheckOnSquare() != NULL){
					Location tmp = mouse->CheckOnSquare()->get_loc();
					Character* cmp = mouse->CheckOnCharacter();

					IDirect3DTexture9* tx = (cmp != NULL)? cmp->get_pSquareOverTexture(): image->Square_Over_Texture;

					DrawTexture(tx, CooToPxl(tmp), 1.0f, 0.0f);
				}

				if (mouse->get_status() == clk_chara){
					Character* cmp = turn->get_character();

					cmp->Draw(clicked);

					for (int i = 0; i < cmp->get_numMoveable(); ++i)
						DrawTexture(image->Square_Moveable_Texture, CooToPxl(cmp->get_moveableList()[i]), 1.0f, 0.0f);
				}
				
				Sprite->End();
	
				Device->EndScene();
			}

			Device->Present(0, 0, 0, 0);
		}
	}
	
	// TO DELETE/Free/Release LIST
	// Board::board[9][9]
	// _board
	// characters	+	vector moveableList
	// players
	// IDirect3DTexture***

	image->ReleaseTextures();
	ReleaseDevice();

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage){
	case WM_LBUTTONDOWN:
		mouse->Click(turn);
		/*
		if (mouse->CheckOnCharacter() != NULL){
			mouse->set_status(clk_chara);
			mouse->CheckOnCharacter()->get_num();
			// impl.
		}
		// impl.
		*/

		return 0;

	case WM_LBUTTONUP:
		return 0;

	case WM_MOUSEMOVE:
		mouse->__set_loc(LOWORD(lParam), HIWORD(lParam));
		return 0;
		
	case WM_KEYDOWN:
		/*
		if(wParam == VK_ESCAPE) {
			DestroyWindow(hWnd);
			return 0;
		}
		*/
		if(wParam == 'P') {
			// pause?
			return 0;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/*
void KeyInput() {
	//키입력을 받고 받은 키입력에 따라 처리를 결정하는 함수
	//여기서 간단한 winapi에서 쓰기 쉬운 함수인 GetAsyncKeyState를 씀

	//리턴값을 살펴보면
	//GetAsyncKeyState는 키가 눌렸을 때 GetAsyncKeyState의 0x8000 bit가 1이된다.
	//GetAsyncKeyState가 호출되었을 때부터 다음 GetAsyncKeyState가 호출될 때까지 
	//키가 계속 눌려 있는 상태라면 0x0001 bit는 0, 그렇지 않은 경우는 1이 된다.

	//간단하게 비트연산자를 이용해서 리턴값을 확인하는데 자주쓰이는 2가지 경우를 예로 들면
	//if((GetAsyncKeyState(원하는키) & 0x8001) == 0x8001) <-키가 막 눌린 상태(누른 순간만 true)
	//if(GetAsyncKeyState(원하는키) & 0x8000) <- 키가 눌린 상태(눌리고 있는 동안 계속 true)
	//같이 사용할 수 있다. 복잡해보이면 위의 2경우만 사용하면 됨

	//인자값은 눌린 키를 뜻하는데 아스키코드를 원하면
	//GetAsyncKeyState('a') , GetAsyncKeyState('b') 이렇게 작은따옴표를 이용해서
	//특수한 키를 원하면
	//GetAsyncKeyState(VK_ESC), GetAsyncKeyState(VK_RETURN)  //순서대로 esc와 엔터
	//이렇게 미리 정의되어있는 상수를 슨다.

	if((GetAsyncKeyState(VK_SPACE) & 0x8001) == 0x8001) {
		//스페이스가 눌린 순간을 뜻한다.
	}

	if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
	}

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	}
}
*/

void GameLoop() {
	// impl.
}