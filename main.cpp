#include <stdlib.h>
#include <time.h>
#include "api.h"
#include "dxfunc.h"
#include "image.h"
#include "mouse.h"
#include "board.h"
#include "player.h"
//#include "fps.h"

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "winmm")
#pragma comment (lib, "dxguid")
#pragma comment (lib, "dinput8")

void KeyInput();
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
	LoadTextures();

	Board* _board = new Board();

	Player* player1 = NULL;
	Player* player2 = NULL;
	Player* turn = NULL;

	Player().InitPlayer(&player1, &player2, &turn);	// TODO: �� ���ϴ°� ����

	while (Message.message != WM_QUIT){
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if (Device){
			Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0);
	
			if (SUCCEEDED(Device->BeginScene())){
				Sprite->Begin(D3DXSPRITE_ALPHABLEND);

				// �ؽ���, x, y, ������, ����
				DrawTexture(Background_Texture, 0, 0, 1.0f, 0.0f); // ���׸�
				_board->Draw();

				player1->get_character()->Draw();
				player2->get_character()->Draw();


				// �ӽ� �׽�Ʈ
				Location tmp;

				if (mouse->CheckOnSquare() != NULL)
					tmp = mouse->CheckOnSquare()->get_loc();
				else{
					tmp.x = -1;
					tmp.y = -1;
				}

				if (tmp.x != -1){
					IDirect3DTexture9* tx;

					if (tmp.x == player1->get_character()->get_loc().x && tmp.y == player1->get_character()->get_loc().y)
						tx = player1->get_character()->get_pSquareOverTexture();
					else if (tmp.x == player2->get_character()->get_loc().x && tmp.y == player2->get_character()->get_loc().y)
						tx = player2->get_character()->get_pSquareOverTexture();
					else
						tx = Square_Over_Texture;

					DrawTexture(tx, CooToPxl(tmp), 1.0f, 0.0f);
				}

				//RECT rc={0, -380, 800, 200};
				// �ؽ�Ʈ�� �׷��� �簢���� ��ǥ�� �ִ´�.
				// ������� left, top, right, bottom�� ��ǥ
				// {0, 0, 0, 0}�� ���� : ���� �ֱٿ� draw�� �׸�



				//���⼭ ��Ʈ�� ����Ѵ�.
				//ù��°����: ��������Ʈ ����̽��� �ִ°�. NULL�� �־ ����� �Ǳ� �Ǵ���
				//�ι�°����: ���ڿ��� �ִ°�
				//����°����: ����� ���ڿ� ���� ������ ��. NULL�� ������ ���ڿ��� -1�� ������ �ȴ�.
				//�׹�°����: �ؽ�Ʈ�� ������ �����Ѵ�. ���⼱ ��������, ���ٸ��׸���, �߸����ʱ� �ɼ���. �ڼ��� ������ Ŭ���� �ø�
				//�ټ���°����: �ؽ�Ʈ �÷�

				//Font->DrawTextA(Sprite, FPS_str, -1, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 0));
				
				Sprite->End();
	
				Device->EndScene();
			}

			Device->Present(0, 0, 0, 0);
		}
	}
	
	// TO DELETE LIST
	// Board::board[9][9]
	// _board
	// character 1, 2
	// player 1, 2

	ReleaseTextures();
	ReleaseDevice();

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch(iMessage) {
	case WM_LBUTTONDOWN:
		if (mouse->CheckOnSquare()->get_loc().x != -1){
			if (Board::board[mouse->CheckOnSquare()->get_loc().y][mouse->CheckOnSquare()->get_loc().x]->get_onthis() != NULL){
				Board::board[mouse->CheckOnSquare()->get_loc().y][mouse->CheckOnSquare()->get_loc().x]->get_onthis()->get_num();
			}
		}

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

void GameLoop() {
	// impl.
}