#include "api.h"
#include "dxfunc.h"
#include "image.h"
#include "player.h"
#include "board.h"

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
	
	// 게임의 텍스쳐 로딩
	LoadTexture("Image/background.png", &Background_Texture);
	LoadTexture("Image/board.png", &Board_Texture);
	LoadTexture("Image/character_black.png", &Character_Black_Texture);
	LoadTexture("Image/character_brown.png", &Character_Brown_Texture);

	//init
	Board* board = new Board();
	Player* player1 = new Player(Character_Black_Texture, 0, 4);	/////
	Player* player2 = new Player(Character_Brown_Texture, 8, 4);	/////

	while (Message.message != WM_QUIT){
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if (Device){
			Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0);
	
			if (SUCCEEDED(Device->BeginScene())){
				Sprite->Begin(D3DXSPRITE_ALPHABLEND);

				// 텍스쳐, x, y, 사이즈, 각도.
				DrawTexture(Background_Texture, 0, 0, 1.0f, 0.0f); // 배경그림
				board->DrawBoard();

				player1->get_character()->Draw(board->get_loc());
				player2->get_character()->Draw(board->get_loc());

				//RECT rc={0, -380, 800, 200};
				// 텍스트가 그려질 사각형의 좌표를 넣는다.
				// 순서대로 left, top, right, bottom의 좌표
				// {0, 0, 0, 0}의 기준 : 가장 최근에 draw한 그림



				//여기서 폰트를 출력한다.
				//첫번째인자: 스프라이트 디바이스를 넣는곳. NULL을 넣어도 출력은 되긴 되더라
				//두번째인자: 문자열을 넣는곳
				//세번째인자: 출력할 문자열 내의 문자의 수. NULL로 끝나는 문자열은 -1을 넣으면 된다.
				//네번째인자: 텍스트의 포맷을 설정한다. 여기선 왼쪽정렬, 한줄만그리기, 잘리지않기 옵션임. 자세한 설명은 클럽에 올림
				//다섯번째인자: 텍스트 컬러

				//Font->DrawTextA(Sprite, FPS_str, -1, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 0));
				
				Sprite->End();
	
				Device->EndScene();
			}

			Device->Present(0, 0, 0, 0);
		}
	}
	
	ReleaseTexture();
	Device_Release();

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	static int mx, my;

	switch(iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		//mx    =    LOWORD(lParam);
		//my    =    HIWORD(lParam);

		return 0;

	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

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