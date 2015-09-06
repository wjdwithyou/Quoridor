#include "api.h"
#include "dxfunc.h"
#include "image.h"
#include "mouse.h"
#include "board.h"
#include "player.h"

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "winmm")
#pragma comment (lib, "dxguid")
#pragma comment (lib, "dinput8")

void KeyInput();
void GameLoop();
float CalcFPS();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Device_Release();

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

	//srand((unsigned)time(NULL));
	
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

	LoadTextures();
	/*
	// ������ �ؽ��� �ε�
	LoadTexture("Image/background.png", &Background_Texture);
	LoadTexture("Image/board.png", &Board_Texture);
	LoadTexture("Image/character_black.png", &Character_Black_Texture);
	LoadTexture("Image/character_brown.png", &Character_Brown_Texture);
	LoadTexture("Image/square_over.png", &Square_Over_Texture);
	LoadTexture("Image/square_over_black.png", &Square_Over_Black_Texture);
	LoadTexture("Image/square_over_brown.png", &Square_Over_Brown_Texture);
	*/
	//init
	//Mouse* mouse = new Mouse();
	Board* board = new Board();
	Player* player1 = new Player(Character_Black_Texture, 0, 4);
	Player* player2 = new Player(Character_Brown_Texture, 8, 4);

	while (Message.message != WM_QUIT){
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if (Device){
			Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0);
	
			if (SUCCEEDED(Device->BeginScene())){
				Sprite->Begin(D3DXSPRITE_ALPHABLEND);

				// �ؽ���, x, y, ������, ����.
				DrawTexture(Background_Texture, 0, 0, 1.0f, 0.0f); // ���׸�
				board->DrawBoard();

				player1->get_character()->Draw(board->get_loc());
				player2->get_character()->Draw(board->get_loc());



				Location tmp = mouse->CheckOnSquare(board->get_loc());

				if (tmp.x != -1)
					DrawTexture(Square_Over_Texture, CooToPxl(board->get_loc().x, tmp.x), CooToPxl(board->get_loc().y, tmp.y), 1.0f, 0.0f);

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
	
	ReleaseTextures();
	Device_Release();

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		//impl.

		return 0;

	case WM_MOUSEMOVE:
		mouse->set_loc(LOWORD(lParam), HIWORD(lParam));

		return 0;
		
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE) {
			DestroyWindow(hWnd);
			return 0;
		}
		if(wParam == 'P') {
			// pause?
		}
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

void Device_Release() {
	if(Sprite != NULL) {
		Sprite -> Release();
		Sprite = NULL;
	}
	if(Device != NULL) {
		Device -> Release();
		Device = NULL;
	}
	if(Font != NULL) {
		Font -> Release();
		Font = NULL;
	}
}