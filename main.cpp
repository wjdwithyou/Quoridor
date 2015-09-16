#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

	// ������ �ؽ��� �ε�
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
		sprintf_s(debug->sz_fps, "%02.2fFPS", debug->CalcFPS()); // �������� ���ڿ��� ���� sz_fps�� ����

		sprintf_s(debug->sz_cturn, "%d player", turn->get_character()->get_num() + 1);
		sprintf_s(debug->sz_pxl_x, "pxl.x: %4d", mouse->get_pxloc().x);
		sprintf_s(debug->sz_pxl_y, "pxl.y: %4d", mouse->get_pxloc().y);
		sprintf_s(debug->sz_loc_x, "loc.x: %4d", mouse->get_locoo().x);
		sprintf_s(debug->sz_loc_y, "loc.y: %4d", mouse->get_locoo().y);
		sprintf_s(debug->sz_mstat, "mstat: %4d", mouse->get_status());

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
				
				if (mouse->CheckOnSquare() != NULL)		// mouse
					mouse->DrawEffect();
					

				for (int i = 0; i < Player().get_numPlayer(); ++i)		// character
					playerList[i]->get_character()->Draw();
				
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
		break;

	case WM_LBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		mouse->__set_loc(LOWORD(lParam), HIWORD(lParam));
		break;
		
	case WM_KEYDOWN:
		/*
		if(wParam == VK_ESCAPE) {
			DestroyWindow(hWnd);
			return 0;
		}
		*/
		if(wParam == 'P') {
			// pause?
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/*
void KeyInput() {
	//Ű�Է��� �ް� ���� Ű�Է¿� ���� ó���� �����ϴ� �Լ�
	//���⼭ ������ winapi���� ���� ���� �Լ��� GetAsyncKeyState�� ��

	//���ϰ��� ���캸��
	//GetAsyncKeyState�� Ű�� ������ �� GetAsyncKeyState�� 0x8000 bit�� 1�̵ȴ�.
	//GetAsyncKeyState�� ȣ��Ǿ��� ������ ���� GetAsyncKeyState�� ȣ��� ������ 
	//Ű�� ��� ���� �ִ� ���¶�� 0x0001 bit�� 0, �׷��� ���� ���� 1�� �ȴ�.

	//�����ϰ� ��Ʈ�����ڸ� �̿��ؼ� ���ϰ��� Ȯ���ϴµ� ���־��̴� 2���� ��츦 ���� ���
	//if((GetAsyncKeyState(���ϴ�Ű) & 0x8001) == 0x8001) <-Ű�� �� ���� ����(���� ������ true)
	//if(GetAsyncKeyState(���ϴ�Ű) & 0x8000) <- Ű�� ���� ����(������ �ִ� ���� ��� true)
	//���� ����� �� �ִ�. �����غ��̸� ���� 2��츸 ����ϸ� ��

	//���ڰ��� ���� Ű�� ���ϴµ� �ƽ�Ű�ڵ带 ���ϸ�
	//GetAsyncKeyState('a') , GetAsyncKeyState('b') �̷��� ��������ǥ�� �̿��ؼ�
	//Ư���� Ű�� ���ϸ�
	//GetAsyncKeyState(VK_ESC), GetAsyncKeyState(VK_RETURN)  //������� esc�� ����
	//�̷��� �̸� ���ǵǾ��ִ� ����� ����.

	if((GetAsyncKeyState(VK_SPACE) & 0x8001) == 0x8001) {
		//�����̽��� ���� ������ ���Ѵ�.
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